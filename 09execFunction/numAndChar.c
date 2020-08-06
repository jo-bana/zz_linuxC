#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char **argv)
{
	if(argc!=3)
	{
		printf("your input error!\n");
		printf("Usage: %s <types> <count>\n",argv[0]);
		printf("example: %s letter 15\n",argv[0]);
		printf("example: %s number 18\n",argv[0]);
		return -1;
	}
	int i;
	if(0==strcmp(argv[1],"letter"))
	{
		if(atoi(argv[2])>26||atoi(argv[2])<1)
		{
			printf("parameter 2 error!\n");
			return -1;
		}
		
		while(1)
		{
			for(i='a';i<'a'+atoi(argv[2]);i++)
			{
				printf("%c",i);
			}
			printf("\n");
			sleep(2);
		}
	}
	else if(0==strcmp(argv[1],"number"))
	{
		if(atoi(argv[2])<1)
		{
			printf("parameter 2 error!\n");
			return -1;
		}
		while(1)
		{
			for(i=1;i<=atoi(argv[2]);i++)
			{
				printf("%d ",i);
			}
			printf("\n");
			sleep(2);
		}
	}
}
