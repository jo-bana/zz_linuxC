#include "common.h"

char g_input_cmd[SRT_LEN];
char g_buffer[BUF_SIZE];

void welcomeAndBye(int nSide)
{
		printf("******************************************************\n");
	
	if(0==nSide)
	{
		printf("*************Welcome to Message Send System***********\n");
		printf("********you can input anything to zzRecord.log********\n");
		printf("****************if you want to quit*******************\n");
		printf("***************please input \"quit\"******************\n");
	}
	else
	{
		printf("***********************Goodbye!***********************\n");
	}
	
		printf("******************************************************\n");
}


void sendmasssage(int sockfd)
{
	char temp[BUF_SIZE];
	memset(g_buffer,0,sizeof(g_buffer));
	send(sockfd,g_input_cmd,strlen(g_input_cmd)+1,0);
}


int main(int argc,char **argv)
{
	if(argc!=2)
	{
		printf("please enter the server's hostname!\n");
		printf("Usage:%s xxx.xxx.xxx.xxx\n",argv[0]);
		printf("example:%s 127.0.0.1\n",argv[0]);
		exit(1);
	}

	//通信套接字
	int sockfd;
	int recvBytes;
	unsigned char buffer[BUF_SIZE];

	//ip地址结构体
	struct hostent *host;

	//server 地址结构体
	struct sockaddr_in server_addr;

	//解析并将字符串ip转化成ip结构体中
	host=gethostbyname(argv[1]);
	if(NULL==host)
	{
		printf("host name error!\n");
		exit(1);
	}

	//创建通信套接字
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		printf("socket create error!\n");
		exit(1);
	}

	//填充服务器的ip地址和端口地址结构体
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORT);
	server_addr.sin_addr=*((struct in_addr*)host->h_addr);
	bzero(&(server_addr.sin_zero),8);

	//请求连接服务器
	if(connect(sockfd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr))<0)
	{
		printf("connect error!\n");
		exit(1);
	}
	printf("connect sueccess!\n");
	
	//print welocome interface
	welcomeAndBye(0);
	
	printf("please input a string:");
	while(1)
	{
		memset(g_input_cmd,0,sizeof(g_input_cmd));
		scanf("%s",g_input_cmd);
		send(sockfd,g_input_cmd,strlen(g_input_cmd)+1,0);
		if(0==strcmp("quit",g_input_cmd))
		{
			break;
		}
		else
		{
			sendmasssage(sockfd);
		}
	}
	close(sockfd);	
	//print end interface

	welcomeAndBye(1);
	return 0;
}

