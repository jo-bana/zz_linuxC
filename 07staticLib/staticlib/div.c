#include <stdio.h>

int Idiv(int a,int b)
{
 	if(b==0)
 	{	
 		printf("the div can't be zero!\n");
		return -1;
 	}
	return (a/b);
}
float Fdiv(float a,float b)
{
 	if(b<0.00001 && b>-0.00001)
 	{	
 		printf("the div can't be zero!\n");
		return -1;
 	}
	return (a/b);
}

