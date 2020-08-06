#include <stdio.h>
#include <string.h>
#include "uart.h"

int main(int argc,char **argv)
{
	int rtn;
	int Count = 0;
	char enter[]="\n";//assign 2 sapce
	unsigned char buf[1024];
	if(argc!=2)
	{
		printf("Input error!\n");
		printf("Usage: %s <Device>\n",argv[0]);
		printf("Example: %s /dev/ttyUSB0\n",argv[0]);
		return -1;
	}
	rtn = SerialOpen(argv[1]);
	if(0>rtn)
	{
		printf("device %s open error!\n",argv[1]);
		return -1;
	}
	rtn = SerialConfig(115200,8,'n',1);
	if(0>rtn)
	{
		printf("device %s configure error!\n",argv[1]);
		SerialClose();
		return -1;
	}
	while(1)
	{
		//get first number
		bzero(buf,sizeof(buf));
		printf("please input first number:");
		scanf("%s",buf);
		if(0==strcmp("quit",buf))
		{
			break;
		}
		strcat(buf,enter);
		SerialSend(buf,strlen(buf));
		//get second number
		bzero(buf,sizeof(buf));
		printf("please input second number:");
		scanf("%s",buf);
		if(0==strcmp("quit",buf))
		{
			break;
		}
		strcat(buf,enter);
		SerialSend(buf,strlen(buf));
		//receive result
		bzero(buf,sizeof(buf));
		rtn = SerialReceive(buf,sizeof(buf));
		if(rtn<0)
		{
			printf("COM receive failure!\n");			
		}
		else
		{
			printf("the result:%s\n",buf);
		}
	}
	SerialClose();
}
