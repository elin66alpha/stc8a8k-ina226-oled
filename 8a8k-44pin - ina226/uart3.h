#include <STC8.H>
#define	U8 unsigned char
#define U16 unsigned int
//此头文件专为UART3串口3所写，串口三寄存器不能位寻址


void Uart3Init(void)		//9600bps@11MHz
{
	S3CON = 0x10;		//8λ����,�ɱ䲨����
	S3CON &= 0xBF;		//����3ѡ��ʱ��2Ϊ�����ʷ�����
	AUXR &= 0xFB;		//��ʱ��2ʱ��ΪFosc/12,��12T
	T2L = 0xE8;		//�趨��ʱ��ֵ
	T2H = 0xFF;		//�趨��ʱ��ֵ
	AUXR |= 0x10;		//������ʱ��2
		P_SW2 |= 0x02;		// P5.1,,P5.0	选择io
		IE2 |=  ES3;//串口3使能中断
		EA=1;
}

