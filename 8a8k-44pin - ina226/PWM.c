#include "pwm.h"

#define CYCLE 0x7fff

void Pwm_Init()//io最多八个，输入0-7
{
    P_SW2 |= EAXFR;
    PWMCKS = 0x00;
    PWMC = CYCLE;

        PWM0T1 = 0x0000;
        PWM0T2 = 0x0001;
        PWM0CR = 0x80;

        PWM1T1 = 0x0000;
        PWM1T2 = 0x0001;
        PWM1CR = 0x80;

        PWM2T1 = 0x0000;
        PWM2T2 = 0x0001;
        PWM2CR = 0x80;

        PWM3T1 = 0x0000;
        PWM3T2 = 0x0001;
        PWM3CR = 0x80;

        PWM4T1 = 0x0000;
        PWM4T2 = 0x0001;
        PWM4CR = 0x80;

        PWM5T1 = 0x0000;
        PWM5T2 = 0x0001;
        PWM5CR = 0x80;

        PWM6T1 = 0x0000;
        PWM6T2 = 0x0001;
        PWM6CR = 0x80;

        PWM7T1 = 0x0000;
        PWM7T2 = 0x0001;
        PWM7CR = 0x80;

    P_SW2 &= ~EAXFR;
    PWMCR = 0xc0;
    EA = 1;
}

