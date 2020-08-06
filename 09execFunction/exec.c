#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_STRING 256

void main()
{
	char *p[MAX_STRING]={"numAndChar","letter","16",(char*)0};
	char *q[MAX_STRING]={"numAndChar","number","13",(char*)0};
	pid_t result;
	result=fork();
	if(-1==result)
	{
		printf("fork error!\n");
		return;
	}
	else if(0==result)
	{
		//call numAndChar program in son process and print word 
		#if 0
		if(execl("./numAndChar","numAndChar","letter","16",NULL)<0)
		{
			printf("letter failure!\n");
		}
		#endif
		if(execv("./numAndChar",p)<0)
		{
			printf("letter failure!\n");
		}
	}
	else
	{
		//call numAndChar program in son process and print number
		#if 0
		if(execl("./numAndChar","numAndChar","number","13",NULL)<0)
		{
			printf("letter failure!\n");
		}
		#endif
		if(execv("./numAndChar",q)<0)
		{
			printf("letter failure!\n");
		}
	}
}

