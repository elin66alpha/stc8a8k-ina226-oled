
#include <STC8.H>
#include "oled.h"
	
#include "intrins.h"
#include "oledfont.h"  

void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
			{

   Write_IIC_Data(dat);
   
		}
	else {
   Write_IIC_Command(dat);
		
	}


}

/********************************************
// fill_Picture
********************************************/
//void fill_picture(unsigned char fill_Data)
//{
//	unsigned char m,n;
//	for(m=0;m<8;m++)
//	{
//		OLED_WR_Byte(0xb0+m,0);		//page0-page1
//		OLED_WR_Byte(0x00,0);		//low column start address
//		OLED_WR_Byte(0x10,0);		//high column start address
//		for(n=0;n<128;n++)
//			{
//				OLED_WR_Byte(fill_Data,1);
//			}
//	}
//}



void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD); 
}   	  
////开启OLED显示    
//void OLED_Display_On(void)
//{
//	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
//	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
//	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
//}
////关闭OLED显示     
//void OLED_Display_Off(void)
//{
//	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
//	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
//	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
//}		   			 
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!
	  
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //更新显示
}
//void OLED_On(void)  
//{  
//	u8 i,n;		    
//	for(i=0;i<8;i++)  
//	{  
//		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
//		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
//		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
//		for(n=0;n<128;n++)OLED_WR_Byte(1,OLED_DATA); 
//	} //更新显示
//}
//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示				 
//size:选择字体 16/12 
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//得到偏移后的值			
		if(x>Max_Column-1){x=0;y=y+2;}
		if(Char_Size ==16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
			}
			else {	
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
				OLED_WR_Byte(F6x8[c][i],OLED_DATA);
				
			}
}

//显示单个数字
//void OLED_Showm(u8 x,u8 y,u16 num,u8 size2)
//{  
//	u8 i,f,g;
//	if(num>>15)//负温度
//	{
//		num=num&0x7fff;//高位清零
//	  i=num/100;
//	  f=num%100/10;
//	  g=num%10;
//	  OLED_ShowChar(x,y,'-',size2);
//		OLED_ShowChar(x+size2/2,y,f+'0',size2);
//	  OLED_ShowChar(x+size2,y,'.',size2);
//	  OLED_ShowChar(x+size2+4,y,g+'0',size2);
//}
//else
//{
//   i=num/100;
//	f=num%100/10;
//	g=num%10;
//	OLED_ShowChar(x,y,i+'0',size2);
//	OLED_ShowChar(x+size2/2,y,f+'0',size2);
//	OLED_ShowChar(x+size2,y,'.',size2);
//	OLED_ShowChar(x+size2+4,y,g+'0',size2);
//
//
//}}
//m^n函数
//u16 oled_pow(u8 m,u8 n)
//{
//	u16 result=1;	 
//	while(n--)result*=m;    
//	return result;
//}				  
//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  

void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],Char_Size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}
u16 oled_pow(u8 m,u8 n)
{
	u16 result=1;	 
	while(n--)result*=m;    
	return result;
}		
void OLED_ShowNum(u8 x,u8 y,u16 num,u8 len,u8 size2)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
} 
//显示汉字
//void OLED_ShowCHinese(u8 x,u8 y,u8 no)
//{      			    
//	u8 t,adder=0;
//	OLED_Set_Pos(x,y);	
//    for(t=0;t<16;t++)
//		{
//				OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
//				adder+=1;
//     }	
//		OLED_Set_Pos(x,y+1);	
//    for(t=0;t<16;t++)
//			{	
//				OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
//				adder+=1;
//      }					
//}
/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
//void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
//{ 	
// unsigned int j=0;
// unsigned char x,y;
//  
//  if(y1%8==0) y=y1/8;      
//  else y=y1/8+1;
//	for(y=y0;y<y1;y++)
//	{
//		OLED_Set_Pos(x0,y);
//    for(x=x0;x<x1;x++)
//	    {      
//	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
//	    }
//	}
//} 

//初始化SSD1306					    
void OLED_Init(void)
{ 	
 
OLED_WR_Byte(0xAE,OLED_CMD); //关闭显示display off
	OLED_WR_Byte(0x20,OLED_CMD);	//Set Memory Addressing Mode	
	OLED_WR_Byte(0x10,OLED_CMD);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET,OLED_CMD);11,Invalid
	OLED_WR_Byte(0xb0,OLED_CMD);	//Set Page Start Address for Page Addressing Mode,0-7
	OLED_WR_Byte(0xc8,OLED_CMD);	//Set COM Output Scan Direction
	OLED_WR_Byte(0x02,OLED_CMD); //-设置低位列地址set low column address 注意：0.96屏幕从0x00开始写数据，1.3寸屏幕从0x02开始写数据
	OLED_WR_Byte(0x10,OLED_CMD); //-设置高位列地址set high column address
	OLED_WR_Byte(0x40,OLED_CMD); //--set start line address
	OLED_WR_Byte(0x81,OLED_CMD); //--set contrast control register
	OLED_WR_Byte(0xff,OLED_CMD); //亮度调节 0x00~0xff
	OLED_WR_Byte(0xa1,OLED_CMD); //--set segment re-map 0 to 127
	OLED_WR_Byte(0xa6,OLED_CMD); //--set normal display
	OLED_WR_Byte(0xa8,OLED_CMD); //--set multiplex ratio(1 to 64,OLED_CMD)
	OLED_WR_Byte(0x3F,OLED_CMD); //
	OLED_WR_Byte(0xa4,OLED_CMD); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	OLED_WR_Byte(0xd3,OLED_CMD); //-设置显示偏移set display offset
	OLED_WR_Byte(0x00,OLED_CMD); //-没有偏移not offset
	OLED_WR_Byte(0xd5,OLED_CMD); //-设置时钟分频因子,震荡频率set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0xf0,OLED_CMD); //--set divide ratio
	OLED_WR_Byte(0xd9,OLED_CMD); //--set pre-charge period
	OLED_WR_Byte(0x22,OLED_CMD); //
	OLED_WR_Byte(0xda,OLED_CMD); //--设置COM硬件引脚配置set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);//[5:4]配置
	OLED_WR_Byte(0xdb,OLED_CMD); //--set vcomh
	OLED_WR_Byte(0x20,OLED_CMD); //0x20,0.77xVcc
	OLED_WR_Byte(0x8d,OLED_CMD); //-电荷泵设置set DC-DC enable
	OLED_WR_Byte(0x14,OLED_CMD); //bit2，开启/关闭
	OLED_WR_Byte(0xaf,OLED_CMD); //-开启显示 turn on oled panel
}  


