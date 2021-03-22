#ifndef __GKBASEUSART_H_
#define __GKBASEUSART_H_

#include "usart.h" 

typedef void (*rxIsrCb)	(uint8_t);

typedef struct
{
	UART_HandleTypeDef *huart; //来自HAL的模块
  rxIsrCb  rxf;
	uint8_t  *rxBuf;//放置数据的-不是数组了这样灵活点儿
	uint16_t rx_len;
	uint8_t  one;//当前过来的HEX
	uint8_t  received2idle;//1空闲中断到了
}GK_USARTBASE_TYPE ;	 

typedef struct
{
   void                  (*clear)(GK_USARTBASE_TYPE *myuart);
   GK_USARTBASE_TYPE*    (*read) (uint8_t id);
   void                  (*tx)   (GK_USARTBASE_TYPE *myuart,uint8_t *TX , uint16_t TXlen);
   uint8_t               (*txrx) (GK_USARTBASE_TYPE *myuart, void *Tx ,uint16_t TXlen ,uint8_t *RX,uint16_t *RXlen);
   uint16_t              (*rx)   (GK_USARTBASE_TYPE *myuart,uint8_t *RX , uint16_t *RXlen,uint16_t timeout);
   uint8_t               (*init) (GK_USARTBASE_TYPE *myuart,uint8_t usartid,uint8_t * buf,rxIsrCb rxf);
}GK_USARTBASEFUNCTION_TYPE ;	 


extern GK_USARTBASE_TYPE GKU2;
extern GK_USARTBASE_TYPE GKU1;


extern uint8_t GK_usart_init(GK_USARTBASE_TYPE *myuart,uint8_t usartid,uint8_t* buf,rxIsrCb rxf);
extern uint8_t GK_usart_TXRX(GK_USARTBASE_TYPE  *myuart, void *Tx ,uint16_t TXlen ,uint8_t *RX,uint16_t *RXlen);
extern void GK_usart_clear(GK_USARTBASE_TYPE *myuart);//收发前后
extern void GK_UART_RxIdleCallback(GK_USARTBASE_TYPE *huart);//IT中！
extern GK_USARTBASE_TYPE * GK_usart_read_obj( uint8_t usartid);

#endif
