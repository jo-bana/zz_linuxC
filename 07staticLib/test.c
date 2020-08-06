#include <stdio.h>
#include "staticlib.h"

void main()
{
	int x,y;
	float m,n;
	printf("please input first integer:");
	scanf("%d",&x);
	printf("please input second integer:");
	scanf("%d",&y);
	
	printf("four result:\n");
	printf("%d+%d=%d\n",x,y,Iadd(x,y));
	printf("%d-%d=%d\n",x,y,Isub(x,y));
	printf("%d*%d=%d\n",x,y,Imul(x,y));
	printf("%d/%d=%d\n",x,y,Idiv(x,y));
	
	printf("please input first float:");
	scanf("%f",&m);
	printf("please input second float:");
	scanf("%f",&n);
	
	printf("%f+%f=%f\n",m,n,Fadd(x,y));
	printf("%f-%f=%f\n",m,n,Fsub(x,y));
	printf("%f*%f=%f\n",m,n,Fmul(x,y));
	printf("%f/%f=%f\n",m,n,Fdiv(x,y));
}
