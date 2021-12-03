#include "ina226.h"

//初始化INA226
void mx_ina226_init(void)
{	
 
	INA226_SendData(INA226_ADDR1,CFG_REG,0x8000);	//重新启动
	
	INA226_SendData(INA226_ADDR1,CFG_REG,0x484f);	//设置转换时间204us,求平均值次数128，采样时间为204*128，设置模式为分流和总线连续模式
	INA226_SendData(INA226_ADDR1,CAL_REG,CAL);	//设置分辨率
	//INA226_Get_ID(INA226_ADDR1);					//获取ina226的id
}
 
//设置寄存器指针
void INA226_SetRegPointer(u8 addr,u8 reg)
{
	IIC_Start();
 
	Write_IIC_Byte(addr);
	IIC_Wait_Ack();
 
	Write_IIC_Byte(reg);
	IIC_Wait_Ack();
 
	IIC_Stop();
}
 
//发送,写入数据
void INA226_SendData(u8 addr,u8 reg,u16 udata)
{
	u8 temp=0;
	IIC_Start();
 
	Write_IIC_Byte(addr);
	IIC_Wait_Ack();
 
	Write_IIC_Byte(reg);
	IIC_Wait_Ack();
	
	temp = (u8)(udata>>8);
	Write_IIC_Byte(temp);
	IIC_Wait_Ack();
 
	temp = (u8)(udata&0x00FF);
	Write_IIC_Byte(temp);
	IIC_Wait_Ack();
	
	IIC_Stop();
}
 
//读取数据
u16 INA226_ReadData(u8 addr)
{
	u16 temp=0;
	IIC_Start();
 
	Write_IIC_Byte(addr+1);
	IIC_Wait_Ack();
	
	temp = Read_IIC_Byte(1);
	temp<<=8;	
	temp |= Read_IIC_Byte(0);
	
	IIC_Stop();
	return temp;
}

u16 INA226_GetShunt_Current(u8 addr)
{
	u16 temp=0;	
	INA226_SetRegPointer(addr,CUR_REG);
	temp = INA226_ReadData(addr);
	if(temp&0x8000)	temp = ~(temp - 1);	
	return temp;
}
 
//获取id
u32 INA226_Get_ID(u8 addr)
{
	u32 temp=0;
	INA226_SetRegPointer(addr,INA226_GET_ADDR);
	temp = INA226_ReadData(addr);
	return temp;
}
 
//获取校准值
u16 INA226_GET_CAL_REG(u8 addr)
{	
	u32 temp=0;
	INA226_SetRegPointer(addr,CAL_REG);
	temp = INA226_ReadData(addr);
	return (u16)temp;
}
 

u16 INA226_GetVoltage(u8 addr)
{
	u32 temp = 0;
	INA226_SetRegPointer(addr,BV_REG);
	temp = INA226_ReadData(addr);
	return (u16)temp;	
}
 
u16 INA226_GetShuntVoltage(u8 addr)
{
	int temp = 0;
	INA226_SetRegPointer(addr,SV_REG);
	temp = INA226_ReadData(addr);
	if(temp&0x8000)	temp = ~(temp - 1);	
	return (u16)temp;	
}
 

//获取功率装载值,ina226内部计算的的功率，由于未经校准，故不采用
 
u16 INA226_Get_Power(u8 addr)
{
	int temp=0;
	INA226_SetRegPointer(addr,PWR_REG);
	temp = INA226_ReadData(addr);
	return (u16)temp;
}
 
//获取功率,ina226内部计算，不准确，不采用
void Get_Power(float *Power)//W
{
	*Power = (INA226_Get_Power(INA226_ADDR1)*POWER_LSB);
}
