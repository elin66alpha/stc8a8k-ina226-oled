#ifndef __IIC_H
#define __IIC_H	
#include <STC8.H>	

#define  u8 unsigned char 
#define  u16 unsigned int 
#define  u32 unsigned long


void IIC_Init();
void IIC_Wait();
void IIC_Start();

void IIC_Stop();
void IIC_Wait_Ack();
void IIC_Wait_NAck();
u8 Read_IIC_Byte(u8 ack_flag);
void Write_IIC_Byte(u8 IIC_Byte);
void Write_IIC_Command(u8 IIC_Command);
void Write_IIC_Data(u8 IIC_Data);
#endif