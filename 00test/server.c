#include "common.h"

char g_ctl_folder[SRT_LEN];
char g_buffer[BUF_SIZE];

const char filePath[]={"zzRecord.log"};

void recvmessage(int sockfd)
{
	char aa[BUF_SIZE];
	memset(aa,0,sizeof(aa));
	time_t t;
	struct tm *p;
	time(&t);
	p=localtime(&t);

	int fd=-1;
	char buf[BUF_SIZE];
	char temp[BUF_SIZE];
	fd=open(filePath,O_CREAT|O_RDWR,0777);
	if(fd<0)
	{
		return;
	}
	//receive data
	while(1)
	{
		sprintf(aa,"%d-%d-%d %d:%d:%d ",1900+p->tm_year,1+p->tm_mon,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
		
		memset(temp,0,sizeof(temp));
		recv(sockfd,temp,sizeof(temp),0);//receive messages
	
		memset(buf,0,BUF_SIZE);
		sprintf(buf,"%s\n",temp);//store the messages to .log
		strcat(aa,buf);
		write(fd,aa,strlen(aa));
		if(0==strcmp(temp,"quit"))
		{
			exit(1);
		}
	}
	
	printf("file done\n");
	close(fd);
}

int main()
{
	//net communication
	struct sockaddr_in server_sockaddr,client_sockaddr;
	int size;
	int sockfd,listenfd;

	listenfd=socket(AF_INET,SOCK_STREAM,0);
	if(listenfd<0)
	{
		printf("socket create error!\n");
		exit(1);
	}

	//prevent binding error
	int opt=1;
	setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
	
	//绑定本地IP地址和监听端口
	server_sockaddr.sin_family=AF_INET;
	server_sockaddr.sin_port=htons(PORT);
	server_sockaddr.sin_addr.s_addr=INADDR_ANY;
	bzero(&(server_sockaddr.sin_zero),8);
	if(bind(listenfd,(struct sockaddr*)&server_sockaddr,sizeof(struct sockaddr))<0)
	{
		printf("bind error!\n");
		exit(1);
	}

	//用监听套接字进行监听网络连接请求
	if(listen(listenfd,LISTEN_LENGTH)<0)
	{
		printf("listen error!\n");
		exit(1);
	}

	//接受连接
	size=sizeof(struct sockaddr);
	sockfd=accept(listenfd,(struct sockaddr*)&client_sockaddr,&size);
	if(sockfd<0)
	{
		printf("accept error!\n");
		exit(1);
	}

	//print welcome interface
	//welcomeAndBye(0,0);
	while(1)
	{
		memset(g_buffer,0,sizeof(g_buffer));
		recv(sockfd,g_buffer,sizeof(g_buffer),0);
		if(0==strcmp("quit",g_buffer))
		{
			break;
		}
		else
		{
			recvmessage(sockfd);
		}
	}
	close(listenfd);
	close(sockfd);
	return 0;
}
