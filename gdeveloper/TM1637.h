#ifndef   _TM1637_H
#define   _TM1637_H

#include "gpio.h"

//PB10（SCL）,PB11（SDA）
//#define SCL_Pin GPIO_PIN_10
//#define SCL_GPIO_Port GPIOB
//#define SDA_Pin GPIO_PIN_11
//#define SDA_GPIO_Port GPIOB
//DIO和CLK相关引脚的宏定义，用户只需要修改相关宏即可
#define    TM_DIO_PORT    	    GPIOB		                 		
#define    TM_DIO_PIN			GPIO_PIN_11			        

#define    TM_CLK_PORT    	    GPIOB			              		
#define    TM_CLK_PIN		    GPIO_PIN_10			

//时钟线和数据线高低电平的宏定义，不需修改
#define      CLK_1         HAL_GPIO_WritePin(TM_CLK_PORT,TM_CLK_PIN,GPIO_PIN_SET)
#define      CLK_0         HAL_GPIO_WritePin(TM_CLK_PORT,TM_CLK_PIN,GPIO_PIN_RESET)
#define      DIO_1         HAL_GPIO_WritePin(TM_DIO_PORT,TM_DIO_PIN,GPIO_PIN_SET)
#define      DIO_0         HAL_GPIO_WritePin(TM_DIO_PORT,TM_DIO_PIN,GPIO_PIN_RESET)

//相关函数声明  
void GPIO_Config(void);
void I2C_Start(void);
void I2C_stop(void);
void TM1637_WriteBit(unsigned char mBit);
void TM1637_WriteByte(unsigned char Byte);
void TM1637_WriteCommand(unsigned char mData);
void TM1637_WriteData(unsigned char addr,unsigned char mData);
void Time_Display(void);

#endif   /* _TM1673_H*/
/*********************************************END OF FILE**********************/
