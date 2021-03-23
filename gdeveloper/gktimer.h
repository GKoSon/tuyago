#ifndef _GKTIMER_H_
#define _GKTIMER_H_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "stdbool.h"

typedef void    (*time_call_back)(void);

//节点的结构体
//因为我放弃了malloc只能参数自己携带内存 所以也对外提供节点的结构体
typedef struct  _time
{
	void        *next;
	uint8_t     handle;
	uint8_t     start;
	uint32_t    cnt;
	uint32_t    time_out;
	void        (*fun)(void);
}gtime_type;

//再次抽象 句柄结构体
typedef struct
{
    uint8_t (*creat) (  gtime_type *timenode ,uint32_t time_out ,uint8_t start, time_call_back call_back);
    uint8_t (*stop)  (  uint8_t  handle);
    uint8_t (*start) (  uint8_t  handle);
}time_ops_type;



//对外提供的句柄
extern time_ops_type   gkTimer;

//周期轮训业务 轮训链表的函数
void gtimer_loop( void );


#endif