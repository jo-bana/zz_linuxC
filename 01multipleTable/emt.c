#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 	1024
#define MIN_STRING 	32
#define ERROR 		-1
#define OK 		 	0
const char fileParth2[]={"EnglishMultiplicationTable"};

const char num1[][BUF_SIZE]={"one","two","three","four","five"."six","seven","eight","nine","ten"};
const char num2[][BUF_SIZE]={"eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
const char num3[][BUF_SIZE]={"twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};


typedef struct
{
	int number;
	char word[MIN_STRING];
}codelist;

codelist cList[]=
{
		{1,"one"},
		{2,"two"},
		{3,"three"},
		{4,"four"},
		{5,"five"},
		{6,"six"},
		{7,"seven"},
		{8,"eight"},
		{9,"nine"},
		{10,"ten"},
		{12,"twelve"},
		{14,"forteen"},
		{15,"fifteen"},
		{16,"sixteen"},
		{18,"eighteen"},
		{20,"twenty"},
		{21,"twenty-one"},
		{24,"twenty-four"},
		{25,"twenty-five"},
		{27,"twenty-seven"},
		{28,"twenty-eight"},
		{30,"thirty"},
		{32,"thirty-two"},
		{35,"thirty-five"},
		{36,"thirty-six"},
		{40,"forty"},
		{42,"forty-two"},
		{45,"forty-five"},
		{48,"forty-eight"},
		{49,"forty-nine"},
		{54,"fifty-four"},
		{56,"fifty-six"},
		{63,"sixty-three"},
		{64,"sixty-four"},
		{72,"seven-two"},
		{81,"eight-one"}
};

int findPosition(int number)
{
	int i;
	for(i=0;i<sizeof(cList)/sizeof(codelist);i++)
	{
		if(number == cList[i].number)
		{
			return i;
		}
	}
	printf("code list haven't the number:%d\n",number);
	return -1;
}

void main()
{
	int i,j;
	int fp=-1;
	char buf[MIN_STRING];
	fp=open(fileParth2,O_CREAT|O_RDWR,0777);
	if(fp<0)
	{
		printf("%s create failture!\n",fileParth2);
		return;
	}
	else
	{
		printf("%s create success!\n",fileParth2);
	}
	
	for(i=1;i<=9;i++)
	{
		for(j=1;j<=i;j++)
		{
			memset(buf,0,BUF_SIZE);
			sprintf(buf,"%6s*%6s=%12s\t",cList[findPosition(i)].word,cList[findPosition(j)].word,cList[findPosition(i*j))].word);
			write(fp,buf,strlen(buf));
		}
		write(fp,"\n",1);
	}
	printf("file done!\n");
	close(fp);
}


#if 0
char* change(int i,int j)
{
	int a,mul;
	char result[][BUF_SIZE]={0};
	mul=i*j;
	//<0
	if((mul/10)<=0)
	{
		return ERROR;
	}
	//1~10
	else if((mul/10)<=1)
	{	
		result[0]=num1[(mul-1)%10];
	}
	//11~19
	else if((mul/10)<2 )
	{	
		result[0]=num2[(mul-1)%10];
	}
	//20~99
	else if((mul/10)<10)
	{
		if(0==mul%10)
		{
			result[0]=num3[(mul-1)%10];
		}
		else
		{
			result[0]=strcat(num3[(mul-1)/10],num1[(mul-1)%10]);
		}
	}
	return result;
}

void main()
{
	int fd2=-1;
	int i,j;
	char c[BUF_SIZE]={0};
	char buf2[BUF_SIZE]={0};
	//打印英文的乘法表
	fd2=open(fileParth2,O_CREAT|O_WRONLY,0777);
	if(fd2<0)
	{
		printf("%s create failture!\n",fileParth2);
		return;
	}
	else
	{
		printf("%s create success!\n",fileParth2);
	}
	for(i=1;i<=9;i++)
	{
		for(j=1;j<=i;j++)
		{
			memset(buf2,0,BUF_SIZE);
			c=change(i,j);
			sprintf(buf2,"%4s*%4s=%4s ",num1[i-1],num1[j-1],c);
			write(fd2,buf2,strlen(buf2));
		}
	}
	
	printf("file done\n");
	close(fd2);
}
#endif
