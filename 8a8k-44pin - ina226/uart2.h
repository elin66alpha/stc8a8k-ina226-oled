#include <STC8.H>
#define	U8 unsigned char
#define U16 unsigned int



void Uart2Init(void)		//4800bps@11.0592MHz
{
	S2CON = 0x50;		//8位数据,可变波特率
	AUXR &= 0xFB;		//定时器时钟12T模式
	T2L = 0xD0;		//设置定时初始值
	T2H = 0xFF;		//设置定时初始值
	AUXR |= 0x10;		//定时器2开始计时
  IE2 |= ES2;
}
