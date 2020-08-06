#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 1024
const char fileParth1[]={"ASCIItable"};
void main()
{
	int fd1=-1;
	int i,j;
	char c;
	char buf1[BUF_SIZE]={0};	
	//¥Ú”°ASCII±Ì
	fd1=open(fileParth1,O_CREAT|O_WRONLY,0777);
	if(fd1<0)
	{
		printf("%s create failture!\n",fileParth1);
		return;
	}
	else
	{
		printf("%s create success!\n",fileParth1);
	}
	for(i=32;i<=126;i++)
	{
		memset(buf1,0,BUF_SIZE);
		//c='i';
		sprintf(buf1,"%c\t%d\n",i,i);
		write(fd1,buf1,strlen(buf1));
	}
	
	printf("file done\n");
	close(fd1);
}

