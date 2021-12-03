#include "main.h"

void main()
{
  	//Pwm_Init();
  	//Uart2Init();
  	//Uart3Init();
	IIC_Init();
  
	OLED_Init(); 
	OLED_Clear(); 
  mx_ina226_init();
  OLED_ShowString(3,0,"INA226:",16);
  OLED_ShowString(3,2,"Voltage:",16);
  OLED_ShowString(3,4,"Current:",16);
  OLED_ShowString(3,6,"Power:",16);
  while(1)
  {
    Voltage = (u16)INA226_GetVoltage(INA226_ADDR1)*Voltage_LSB/100;
    ShuntCurrent = (u16)(INA226_GetShunt_Current(INA226_ADDR1)* CURRENT_LSB)/100;
    Power = Voltage * ShuntCurrent;
		OLED_ShowNum(73,2,Voltage,4,16);
		OLED_ShowNum(73,4,ShuntCurrent,4,16);
		OLED_ShowNum(73,6,Power,4,16);
	
  }
}

