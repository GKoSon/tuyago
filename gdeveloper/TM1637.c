#include "TM1637.h"
#include "main.h"

#define Delay_Us TIM1_Delay
uint8_t  dpFlag = 0;//主函数有说明 
unsigned char  Data[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char  DataDp[]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};
struct {
	char shi;
	char ge;
}Hour;
 
struct {
	char shi;
	char ge;
}Min;



void GPIO_Config(void)
{
 /* GPIO_InitStruct.Pin = LED_Pin|SCL_Pin|SDA_Pin */
}


/*
时钟线为高时，数据线由高变低
*/
void I2C_Start(void)
{
    CLK_1;
    DIO_1;
    Delay_Us(140);

    DIO_0;
    Delay_Us(140);
    CLK_0;
    Delay_Us(140);
}


/*
*时钟线为高时，数据线由低变高
*/
void I2C_stop(void)
{
	
    CLK_0;
    Delay_Us(140);
    DIO_0;
    Delay_Us(140);

    CLK_1;
    Delay_Us(140);	
    DIO_1;
    Delay_Us(140);  	
}


   //写一个比特位
void TM1637_WriteBit(unsigned char mBit)
{
     CLK_0;
     Delay_Us(140);
	
	 if(mBit)
		   DIO_1;
	 else
		   DIO_0;
	 
	 Delay_Us(140);
	 CLK_1;
	 Delay_Us(140);	
}


//写一个字节    
void TM1637_WriteByte(unsigned char Byte)
{
      char loop = 0;
      for(loop = 0;loop<8;loop++)
      {
       TM1637_WriteBit((Byte>>loop) & 0x01);//先写低位	
      }
        CLK_0;
        Delay_Us(140);
        DIO_1;	
        Delay_Us(140);
        CLK_1;		
        Delay_Us(140);
        while(HAL_GPIO_ReadPin(TM_DIO_PORT ,TM_DIO_PIN) == GPIO_PIN_SET);
        //等待应答信号
}
    
/*
*写指令函数
*B7:B6 =01  数据命令控制
*            11地址命令控制
*            10显示命令控制
*/

void TM1637_WriteCommand(unsigned char mData)
{
	I2C_Start();
	TM1637_WriteByte(mData);
	I2C_stop();
}


/*
*@note  写入地址和数据
*/

void TM1637_WriteData(unsigned char addr,unsigned char mData)
{
	I2C_Start();
	TM1637_WriteByte(addr);
	TM1637_WriteByte(mData);
	I2C_stop();
}




/*
控制显示，配置好数据结构体之后，直接调用该函数就可以显示
*/
void Time_Display(void)
{
    TM1637_WriteCommand(0x44);
    TM1637_WriteData(0xc0,Data[Hour.shi]);
    if(dpFlag)
          TM1637_WriteData(0xc1,DataDp[Hour.ge]);
    else
          TM1637_WriteData(0xc1,DataDp[Hour.ge]);

    TM1637_WriteData(0xc2, Data[Min.shi]);
    TM1637_WriteData(0xc2, Data[Min.ge]);
    TM1637_WriteCommand(0x8a);
 }
