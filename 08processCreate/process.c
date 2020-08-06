#include <stdio.h>
#include <string.h>
#include <sys/types.h>

void main()
{
	pid_t result;
	result=fork();
	if(-1==result)
	{
		printf("fork error!\n");
		return;
	}
	//father process
	else if(result>0)
	{
		while(1)
		{
			printf("I am parent,ID:%d,result:%d\n",getpid(),result);
			sleep(1);
		}
	}
	//son process
	else if(0==result)
	{	
		while(1)
		{
			printf("I am son,ID:%d,result:%d\n",getpid(),result);
			printf("My parent ID:%d\n",getppid());
			sleep(3);
		}
	}
}

