#include "tuyamodeuart.h"
#include "stm32f1xx_hal.h"//UART_HandleTypeDef
#include "string.h"
#include <stdio.h>

static GK_USARTBASE_TYPE * uport = NULL;
#define UARTPORT 1 //PC串口TX---PA10 PC串口RX---PA9  此时测试成功 串口发送啥 STM32就返回啥
//#define UARTPORT 2  //PC串口TX---PA3 PC串口RX---PA2  此时测试成功 串口发送啥 STM32就返回啥


uint8_t tuyarxbuf[200];

void tuyamode_init(void)
{
  if( (uport = GK_usart_read_obj(UARTPORT))==NULL)
		return;
	GK_usart_init(uport,UARTPORT,tuyarxbuf,NULL);
}


void tuyamode_tx(uint8_t *TX , uint16_t TXlen  )
{
    HAL_UART_Transmit(uport->huart, TX, TXlen, 0xFFFF);
}


uint8_t tuyamode_txrx(uint8_t *TX , uint16_t TXlen , uint8_t *RX,uint16_t *RXlen )
{
	if(GK_usart_TXRX(uport, TX ,TXlen ,RX,RXlen))
	{
		return 1;
	}
	else
		return 0;
}

void TEST_UARTTXRX(void)
{
	uint8_t TX[]={"send STOP!"};
	uint16_t TXlen=sizeof(TX);
	uint8_t RX[100]={0};
	uint16_t RXlen=0;
	static char goon=0;
	if(goon) return;
	uint8_t rst = tuyamode_txrx(TX , TXlen , RX,&RXlen);
	
	if(rst)
	{
        goon=1;
		tuyamode_tx(RX,RXlen);
	}

}


void TEST_UARTRX(void)
{

	if(uport->received2idle)
	{
		tuyamode_tx(uport->rxBuf,uport->rx_len);
		GK_usart_clear(uport);
	}

}
