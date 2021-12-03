#include "IIC.h"

void IIC_Init()
{
	P_SW2 |= 0xb0;   // SCL(3.2) SDA(3.3)
    I2CCFG = 0xe0;  //开启iic 主机模式 最高速度
	I2CMSST = 0x00; //关中断 待机模式
}

void IIC_Wait()  //等待
{
    while (!(I2CMSST & 0x40));
    I2CMSST &= ~0x40;
}
void IIC_Start()
{
    I2CMSCR = 0x01;     //发送START命令
    IIC_Wait();
}

void IIC_Stop()
{
    I2CMSCR = 0x06;     //发送STOP命令
    IIC_Wait();
}

void IIC_Wait_Ack()
{
    I2CMSST = 0x00;                             //设置ACK信号
    I2CMSCR = 0x05;                             //发送ACK命令
    IIC_Wait();
}

void IIC_Wait_NAck()
{
    I2CMSST = 0x01;                             //设置NACK信号
    I2CMSCR = 0x05;                             //发送ACK命令
    IIC_Wait();
}

u8 Read_IIC_Byte(u8 ack_flag)
{
  I2CMSCR = 0x04;

  if(ack_flag)
  {
     I2CMSST = 0x00;                             //设置ACK信号
      I2CMSCR = 0x05;                             //发送ACK命令
  }
  else
  {
   I2CMSST = 0x01;                             //设置NACK信号
    I2CMSCR = 0x05;                             //发送ACK命令
  }
     IIC_Wait(); 
    return I2CRXD;

}

void Write_IIC_Byte(u8 dat)
{
    I2CTXD = dat;         //写数据到数据缓冲区
    I2CMSCR = 0x02;       //发送SEND命令
    IIC_Wait();
}

void Write_IIC_Command(u8 IIC_Command)
{
   IIC_Start();
   Write_IIC_Byte(0x78);            //Slave address,SA0=0
	IIC_Wait_Ack();	
   Write_IIC_Byte(0x00);			//write command
	IIC_Wait_Ack();	
   Write_IIC_Byte(IIC_Command); 
	IIC_Wait_Ack();	
   IIC_Stop();
}

void Write_IIC_Data(u8 IIC_Data)
{
   IIC_Start();
   Write_IIC_Byte(0x78);			//D/C#=0; R/W#=0
	IIC_Wait_Ack();	
   Write_IIC_Byte(0x40);			//write data
	IIC_Wait_Ack();	
   Write_IIC_Byte(IIC_Data);
	IIC_Wait_Ack();	
   IIC_Stop();
}