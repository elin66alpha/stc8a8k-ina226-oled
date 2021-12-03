#ifndef __TIMER_H__
#define __TIMER_H__

#include <STC8.H>
#include "intrins.h"
 #define	U8 unsigned char
#define U16 unsigned int

void Timer0Init(void);

void Delay1ms();

void Delay(U8 ms);

#endif