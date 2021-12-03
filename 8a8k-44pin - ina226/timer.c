#include "timer.h"
void Timer0Init(void)		//定时器0---1ms--@11.0592MHz
{
	EA = 1;
	ET0 = 1;
	AUXR &= 0x7F;		
	TMOD &= 0xF0;		
	TL0 = 0x66;		
	TH0 = 0xFC;		
	TF0 = 0;		
	TR0 = 1;		
}

void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}

void Delay(U8 ms)
{
	U8 i;
	for(i=0;i<ms;++i)
	{
		Delay1ms();
	}
}