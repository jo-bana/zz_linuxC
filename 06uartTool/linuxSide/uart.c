/************************************************************************************************************* 
 * �ļ���: 	  		uart.c 
 * ����:      		Linux���ڲ�������
 * ����:      		oxp_edward@163.com 
 * ����ʱ��:    	2014��12��31�� 
 * ����޸�ʱ��:	2014��12��31��  
 * ��ϸ:      		��
*************************************************************************************************************/  
#include <stdio.h>         
#include <stdlib.h>        
#include <unistd.h>       
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>        
#include <termios.h>     
#include <errno.h>        
#include <strings.h>
static int SerialPortFd = 0; //���洮�ڵ��ļ�������

/*************************************************************************************************************************
*����        :	int SerialIsValid(void)
*����        : ��鴮���ļ�����������Ч��
*����        : ��
*����        : 0����Ч
			  -1����Ч
*����        : ��
*����        : edward
*ʱ��        : 20141231
*����޸�ʱ��: 20141231
*˵��        : ��
*************************************************************************************************************************/
static int SerialIsValid(void)
{
	//SerialPortFd ��ȫ���
	if(0 == SerialPortFd)
	{
		perror("SerialPortFd is invalid");
		return -1;
	}
	return 0;
}
/*************************************************************************************************************************
*����        :	int SerialIsValid(void)
*����        : ��鴮���ļ�����������Ч��
*����        : ��
*����        : 0����Ч
			  -1����Ч
*����        : ��
*����        : edward
*ʱ��        : 20141231
*����޸�ʱ��: 20141231
*˵��        : ��
*************************************************************************************************************************/
int SerialOpen(const char *devicePath)
{
	SerialPortFd = open(devicePath,O_RDWR | O_NOCTTY);// | O_NDELAY);
	if(SerialPortFd < 0)
	{
		perror(devicePath);
		printf("%s open failed\n",devicePath);
		return -1;
	}
	if(fcntl(SerialPortFd,F_SETFL,0)<0)
  	{
      	printf("fcntl failed!\n");
    }
	return 0;
}
/*************************************************************************************************************************
*����        :	int SerialConfig(int nSpeed,int nBits,char nEvent,int nStop)
*����        : ���ڲ�������
*����        : nSpeed:������
			   nBits :����λ
			   nEvent:��żУ��λ
			   nStop :ֹͣλ
*����        : 0�����óɹ�
			  -1������ʧ��
*����        : ��
*����        : edward
*ʱ��        : 20141231
*����޸�ʱ��: 20141231
*˵��        : ��
*************************************************************************************************************************/
int SerialConfig(int nSpeed,int nBits,char nEvent,int nStop)
{
	int rtn = 0;
	int speed = 0;
	struct termios NewConfig,OldConfig;
	
	//SerialPortFd ��ȫ���
	if(SerialIsValid())
		return -1;
	
	
	//1������ԭ��������
	/*tcgetattr(serialPortFd,&options)�õ���SerialFdָ��������ز�����
	�������Ǳ�����oldtio,�ú���,�����Բ��������Ƿ���ȷ���ô����Ƿ�
	���õȡ������óɹ�����������ֵΪ0��������ʧ�ܣ���������ֵΪ1.*/
	rtn = tcgetattr(SerialPortFd,&OldConfig);
	if(0 != rtn)
	{
		perror("Error on tcgetattr");
		return -1;
	}
	
	bzero(&NewConfig,sizeof(NewConfig));
	
	//2������ѡ��
	//CLOCAL:�޸Ŀ���ģʽ����֤���򲻻�ռ�ô���
	//CREAD:�޸Ŀ���ģʽ������ʹ�ܣ�ʹ���ܹ��Ӵ����ж�ȡ��������
	NewConfig.c_cflag |= CLOCAL | CREAD;
	
	//3����������λ
	//����������λʱ����Ҫ��ʹ��CSIZEλ�������λ����,Ȼ����������Ӧ������λ
	NewConfig.c_cflag &= ~CSIZE;
	switch(nBits)
	{
		case 8: NewConfig.c_cflag |= CS8;break;
		case 7: NewConfig.c_cflag |= CS7;break;
		case 6: NewConfig.c_cflag |= CS6;break;
		case 5: NewConfig.c_cflag |= CS5;break;
		default:
			printf("Error on nBits\n");
			return -1;
	}
	
	//4��������żУ��λ
	//������żУ����Ҫʹ�õ�termiso�е�������Ա��c_cflag��c_iflag,
	//���ȼ���c_cflag�е�У��λʹ�ܱ�־PARENB,�������������ݲ���У��λ��
	//���������ݽ���У���⡣ͬʱ��Ҫ����c_iflag�еĶ����������ݵ���żУ��ʹ��INPCK
	//c_cflag�е�PARODDΪ1ʱʹ����У�飬Ϊ0ʱʹ��żУ��
	switch(nEvent)
	{
		case 'o':
		case 'O': //����Ϊ��У��
			NewConfig.c_cflag |=(PARODD|PARENB);
			NewConfig.c_iflag |= INPCK;
		break;
		case 'e':
		case 'E':  //����ΪżУ��
			NewConfig.c_cflag |=PARENB;
			NewConfig.c_cflag &= ~PARODD;
			NewConfig.c_iflag |= INPCK;
		break;
		case 's':
		case 'S':	/*as no parity*/
			NewConfig.c_cflag &=~PARENB;
			NewConfig.c_cflag &= ~CSTOPB;
		break;
		case 'n':
		case 'N': //��������żУ��λ
			NewConfig.c_cflag &= ~PARENB;
			NewConfig.c_iflag &= ~INPCK;
		break;
		default:	
			printf("Error on nEvent\n");
			return -1;
	}
	
	//5�����ò�����
	switch(nSpeed)
	{
		case 2400: speed = B2400; break;
		case 4800: speed = B4800; break;
		case 9600: speed = B9600; break;
		case 19200: speed = B19200; break;
		case 38400: speed = B38400; break;
		case 115200: speed = B115200; break;
		default:
			printf("Error on nSpeed\n");
			return -1;
	}
	cfsetispeed(&NewConfig,speed);
	cfsetospeed(&NewConfig,speed);
	
	//6������ֹͣλ
	//����ֹͣλ��ͨ������c_cflag�е�CSTOPB��ʵ�ֵġ���ֹͣλΪ1���������CSTOPB����ֹͣλΪ2�����򼤻�CSTOPB
	switch(nStop)
	{
		case 1: NewConfig.c_cflag &= ~CSTOPB;break;
		case 2: NewConfig.c_cflag |=  CSTOPB;break;
		default:
			printf("Error on nStop\n");
			return;
	}
	
	//7�����õȴ�ʱ�����С�����ַ�
	NewConfig.c_cc[VTIME] = 0;//��ȡһ���ַ��ȴ�1*(1/10)s
	NewConfig.c_cc[VMIN] = 1;//��ȡ�ַ������ٸ���

	
	//8��������ڻ���
	//�ڴ����������ú���Ҫ�Ե�ǰ�Ĵ����豸�����ʵ��Ĵ���
	//��ʱ���Ե���tcdrain,tcflow,tcflush�Ⱥ���������Ŀǰ���ڻ������е�����
	//tcdrain ����ʹ����������ֱ������������е�����ȫ���������
	//tcflow  ����������ͣ�����¿�ʼ���
	//tcflush ���������������/���������
	
	//�����������������������ݣ����ǲ��ٶ�ȡ
	
	//TCIFLUSH  // ������յ������ݣ��Ҳ����ȡ������
	//TCOFLUSH  // �����д������ݣ��Ҳ��ᷢ�����նˡ�
	//TCIOFLUSH // ����������ڷ�����I/O���ݡ�
	tcflush(SerialPortFd,TCIFLUSH);
	
	//9����������
	//�ڴ���������ɺ���Ҫʹ��tcsetattr�����������á�
	rtn = tcsetattr(SerialPortFd,TCSANOW,&NewConfig);
	if(0 != rtn)
	{
		perror("Error on tcsetattr");
		return -1;
	}
	
	printf("Serial Set Done\n");
	return 0;
}
/*************************************************************************************************************************
*����        :	int SerialReceive(unsigned char *buf,int size)
*����        :  ���ڽ�������
*����        : buf: ���ջ�����
			   size����������С
*����        :����-1�����ؽ������ݵĴ�С
*����        : ��
*����        : edward
*ʱ��        : 20141231
*����޸�ʱ��: 20141231
*˵��        : ��
*************************************************************************************************************************/
int SerialReceive(unsigned char *buf,int size)
{
	int rtn ;
	//SerialPortFd ��ȫ���
	if(SerialIsValid())
		return -1;
	rtn = read(SerialPortFd,buf,size);
//	printf("ReadLength = %d\n",rtn);
	return rtn;
}
/*************************************************************************************************************************
*����        : int SerialSend(unsigned char *buf,int DataLength)
*����        : ���ڷ�������
*����        : buf�����ͻ�����
			   DataLength����Ҫ���͵��ֽ���
*����        : rtn���ɹ����͵��ֽ���
			  -1������ʧ��
*����        : ��
*����        : edward
*ʱ��        : 20141231
*����޸�ʱ��: 20141231
*˵��        : ��
*************************************************************************************************************************/
int SerialSend(unsigned char *buf,int DataLength)
{
	int rtn ;
	//SerialPortFd ��ȫ���
	if(SerialIsValid())
		return -1;
#if 0
	int remain = DataLength;
	int offset = 0;
	int sub = 0;
	while(remain > 0 )
	{
		sub = (remain >= 8? 8:remain);
		write(SerialPortFd,buf+offset,sub);
		tcflush(SerialPortFd,TCOFLUSH);
		remain -= 8;
		offset += 8;
	}
#else
	rtn = write(SerialPortFd,buf,DataLength);
#endif
	return rtn;	
}
/*************************************************************************************************************************
*����        : int SerialIsValid(void)
*����        : �رմ���
*����        : ��
*����        : 0���رճɹ�
*����        : ��
*����        : edward
*ʱ��        : 20141231
*����޸�ʱ��: 20141231
*˵��        : ��
*************************************************************************************************************************/
int SerialClose(void)
{
	//SerialPortFd ��ȫ���
	if(SerialIsValid())
			return -1;
	close(SerialPortFd);
	return 0;
}
