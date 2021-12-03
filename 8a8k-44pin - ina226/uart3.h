#include <STC8.H>
#define	U8 unsigned char
#define U16 unsigned int
//姝ゅご鏂囦欢涓撲负UART3涓插彛3鎵�鍐欙紝涓插彛涓夊瘎瀛樺櫒涓嶈兘浣嶅鍧�


void Uart3Init(void)		//9600bps@11MHz
{
	S3CON = 0x10;		//8位数据,可变波特率
	S3CON &= 0xBF;		//串口3选择定时器2为波特率发生器
	AUXR &= 0xFB;		//定时器2时钟为Fosc/12,即12T
	T2L = 0xE8;		//设定定时初值
	T2H = 0xFF;		//设定定时初值
	AUXR |= 0x10;		//启动定时器2
		P_SW2 |= 0x02;		// P5.1,,P5.0	閫夋嫨io
		IE2 |=  ES3;//涓插彛3浣胯兘涓柇
		EA=1;
}

