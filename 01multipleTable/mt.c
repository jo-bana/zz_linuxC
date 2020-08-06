#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 1024
const char fileParth[]={"multipleTable"};

void main()
{
	int fd=-1;
	int i,j;
	char c;
	char buf[BUF_SIZE]={0};
	fd=open(fileParth,O_CREAT|O_WRONLY,0777);
	if(fd<0)
	{
		printf("%s create failture!\n",fileParth);
		return;
	}
	else
	{
		printf("%s create success!\n",fileParth);
	}
	//´òÓ¡³Ë·¨±í
	for(i=1;i<=9;i++)
	{
		for(j=1;j<=i;j++)
		{
			memset(buf,0,BUF_SIZE);
			sprintf(buf,"%d*%d=%2d ",j,i,i*j);	
			write(fd,buf,strlen(buf));
		}
		write(fd,"\n",1);
	}
	
	printf("file done\n");
	close(fd);
	
}
