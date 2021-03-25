#ifndef _TUYAMODEUART_H_
#define _TUYAMODEUART_H_

#include "gkbaseusart.h"
void TEST_UARTTXRX(void);
void tuyamode_init(void);
void tuyamode_tx(uint8_t *TX , uint16_t TXlen);
void print_arr(char *name,unsigned char *arr,int len);
#endif
