#include <STC8.H>
#define	U8 unsigned char
#define U16 unsigned int



void Uart2Init(void)		//4800bps@11.0592MHz
{
	S2CON = 0x50;		//8λ����,�ɱ䲨����
	AUXR &= 0xFB;		//��ʱ��ʱ��12Tģʽ
	T2L = 0xD0;		//���ö�ʱ��ʼֵ
	T2H = 0xFF;		//���ö�ʱ��ʼֵ
	AUXR |= 0x10;		//��ʱ��2��ʼ��ʱ
  IE2 |= ES2;
}
