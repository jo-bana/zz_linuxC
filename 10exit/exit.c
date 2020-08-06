#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX_STRING 1024

const char filePath[]="/tmp/writefile";

void integerToAscii(int n,char* str)
{
	char a[MAX_STRING]={0};
	int i=0,j=0;
	do
	{
		a[i++]=n%10+'0';
		n/=10;
	}while(n!=0);

	for(j=0;j<i;j++)
	{
		str[j]=a[i-1-j];
	}
	str[j]='\0';
}

void main(void)
{
	FILE *fp;
	int i;
	char tmp[MAX_STRING];
	fp=fopen(filePath,"w+");
	if(NULL==fp)
	{
		printf("%s open failure!\n",filePath);
		return;
	}
	//from file to write 0~4999  
	for(i=0;i<5000;i++)
	{
		memset(tmp,0,MAX_STRING);
		integerToAscii(i,tmp);
		fwrite(tmp,1,strlen(tmp),fp);		
	}
	//exit(0);
	_exit(0);
}
