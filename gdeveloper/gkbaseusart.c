#include "gkbaseusart.h"
#include "string.h"
#include "stdio.h"

GK_USARTBASE_TYPE GKU1;
GK_USARTBASE_TYPE GKU2;


uint8_t GK_usart_init(GK_USARTBASE_TYPE *myuart,uint8_t usartid,uint8_t * buf,rxIsrCb rxf)
{
	switch(usartid)//绑定关系
	{
    case 1:myuart->huart=&huart1;break;
    case 2:myuart->huart=&huart2;break;
		default :return 0;	
	}
	myuart->rxBuf=buf;
  myuart->rxf=rxf;
	HAL_UART_Receive_IT(myuart->huart, &myuart->one, 1);//开启中断接收 1个1个的接收// 对应 下文
	__HAL_UART_ENABLE_IT(myuart->huart,UART_IT_IDLE);//开启空闲中断
	__HAL_UART_CLEAR_IDLEFLAG(myuart->huart);
	return 1;
}


void GK_usart_clear(GK_USARTBASE_TYPE *myuart)
{
	memset(&myuart->rx_len,0,myuart->rx_len);
	myuart->rx_len=0;
	myuart->received2idle=0;
}


//需要自己放在IT
void GK_UART_RxIdleCallback(GK_USARTBASE_TYPE *myuart)
{
	if(__HAL_UART_GET_FLAG(myuart->huart,UART_FLAG_IDLE))
	{
		__HAL_UART_CLEAR_IDLEFLAG(myuart->huart);

		myuart->received2idle=1;

    printf("#######received2idle####\r\n");

	}
}

//不需要管理 它会自动调用 本来有WEAK
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) //这里扩展一下！！！！
{ 
  if(huart->Instance == USART2) 
	{ 
		GKU2.rxBuf[GKU2.rx_len++%500]=GKU2.one;//V1.0处理 可以 不要 
        GKU2.rxf(GKU2.one); ;//V2.0处理
		HAL_UART_Receive_IT(huart, &GKU2.one, 1) ; 
	}
	else if(huart->Instance == USART1) 
	{ 
		if(GKU1.rxBuf) GKU1.rxBuf[GKU1.rx_len++%1024]=GKU1.one;
        if(GKU1.rxf)   GKU1.rxf(GKU1.one); 
		HAL_UART_Receive_IT(huart, &GKU1.one, 1) ; 
	}

}


uint8_t GK_usart_TXRX(GK_USARTBASE_TYPE  *myuart, void *Tx ,uint16_t TXlen ,uint8_t *RX,uint16_t *RXlen)
{
	uint8_t Cnt = 10,ack=0;
	uint8_t *TX =(uint8_t*)Tx;
//准备工作：
	GK_usart_clear(myuart);

//发送：
	HAL_UART_Transmit(myuart->huart, TX, TXlen, 0xFFFF);
//等待返回：
	while(Cnt--)
	{	
		if(myuart->received2idle)
		{
			ack=1;
			break;
		}
		HAL_Delay(10);//尝试次数 10次   这里面其实需要喂狗 每次这样的情形都有喂狗		
	}
//处理返回：
    if(ack==0)
	return 0; 
   		
	*RXlen=myuart->rx_len;
	memcpy(RX,myuart->rxBuf,myuart->rx_len);
	
//收尾工作：有必要的 比如以后不再TXRX了 只是单纯的RX
	GK_usart_clear(myuart);
	return 1;    
}



//通过ID获得全部结构体 以小博大
GK_USARTBASE_TYPE * GK_usart_read_obj( uint8_t usartid)
{
	switch(usartid)
	{
		case 2:return &GKU2;
		case 1:return &GKU1;
		default :return NULL;	
	}
}


void TX(GK_USARTBASE_TYPE *myuart,uint8_t *TX , uint16_t TXlen)
{
    HAL_UART_Transmit(myuart->huart, TX, TXlen, 0xFFFF);
}

uint16_t RX(GK_USARTBASE_TYPE *myuart,uint8_t *RX , uint16_t *RXlen,uint16_t timeout)
{
    while(1)
    {
        if(myuart->received2idle)
        {
            *RXlen = myuart->rx_len;
            memcpy(RX,myuart->rxBuf,*RXlen);
            printf("--*RXlen %d--\r\n",*RXlen );
            break;
        }
        timeout--;
        if(timeout == 0||timeout == 0XFF)break;
        HAL_Delay(10);
    }
    
    if(timeout == 0)
        return 0;
    else
    {
        GK_usart_clear(myuart);
        return *RXlen;
    }
}
