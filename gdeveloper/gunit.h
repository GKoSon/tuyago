#ifndef GUNIT_H
#define GUNIT_H

#include "gcinclude.h"
#include "stm32f1xx_hal.h"

#ifndef NULL
#define NULL				(void*)(0)
#endif

#ifndef FALSE
#define FALSE				0
#endif
#ifndef TRUE
#define TRUE				!FALSE
#endif

#ifndef BOOL
#define BOOL				bool
#endif
#ifndef false
#define false				FALSE
#endif
#ifndef true
#define true				TRUE
#endif



#define ARRSIZE(ARR)  sizeof(ARR)/sizeof(*ARR)


//https://blog.csdn.net/qq_29796781/article/details/81135198
//Linux彩色打印\e 不行 需要\033
#define NONE                 "\033[0m"
#define BLACK                "\033[0;30m"
#define L_BLACK              "\033[1;30m"
#define RED                  "\033[0;31m"
#define L_RED                "\033[1;31m"
#define GREEN                "\033[0;32m"
#define L_GREEN              "\033[1;32m"
#define BROWN                "\033[0;33m"
#define YELLOW               "\033[1;33m"
#define BLUE                 "\033[0;34m"
#define L_BLUE               "\033[1;34m"
#define PURPLE               "\033[0;35m"
#define L_PURPLE             "\033[1;35m"
#define CYAN                 "\033[0;36m"
#define L_CYAN               "\033[1;36m"
#define GRAY                 "\033[0;37m"
#define WHITE                "\033[1;37m"

#define BOLD                 "\033[1m"
#define UNDERLINE            "\033[4m"
#define BLINK                "\033[5m"
#define REVERSE              "\033[7m"
#define HIDE                 "\033[8m"
#define CLEAR                "\033[2J"
#define CLRLINE              "\r\033[K" 

#define printr(format, arg...) do{printf(RED format NONE,## arg);}while(0)
#define printg(format, arg...) do{printf(GREEN format NONE,## arg);}while(0)
#define printb(format, arg...) do{printf(BLUE format NONE,## arg);}while(0)
#define printk(format, arg...) do{printf(BLACK format NONE,## arg);}while(0)
#define printw(format, arg...) do{printf(WHITE format NONE,## arg);}while(0)
#define printy(format, arg...) do{printf(YELLOW format NONE,## arg);}while(0)
#define printc(format, arg...) do{printf(CYAN format NONE,## arg);}while(0)
#define printp(format, arg...) do{printf(PURPLE format NONE,## arg);}while(0)	
	
#define printlr(format, arg...) do{printf(L_RED format NONE,## arg);}while(0)
#define printlg(format, arg...) do{printf(L_GREEN format NONE,## arg);}while(0)
#define printlb(format, arg...) do{printf(L_BLUE format NONE,## arg);}while(0)
#define printlk(format, arg...) do{printf(L_BLACK format NONE,## arg);}while(0)
#define printlc(format, arg...) do{printf(L_CYAN format NONE,## arg);}while(0)
#define printlp(format, arg...) do{printf(L_PURPLE format NONE,## arg);}while(0)
//printlr 红色 printr
//printlg 绿色
//printlb 蓝色 
//printlc 蓝绿色 printc
//printlk 灰色 不好看
//printlp 紫色  printp
//printy  黄色

#define SHOWME         printf("\r\nHERE %s  %s %d\r\n",__FILE__,__FUNCTION__,__LINE__);
#define NEVERSHOW      printlp("\r\nWHEN U SEE ME ,PAY ATTENTION:%s  %s %d\r\n",__FILE__,__FUNCTION__,__LINE__);
void G_lovexin( void );

void soft_system_resert( const char *funs );

void G_printCHR(void* A,uint8_t len);

void G_printHEX(void* A,uint16_t len);

void G_1byteTo2str(unsigned char* strings,unsigned char* bytes,unsigned char len);

uint8_t is_same(void* a,void* b,uint8_t len);

void print_arr(char *name,unsigned char *arr,int len);

void G_mcuReset(const char *funs);
#endif
