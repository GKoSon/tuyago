#include "gktimer.h"

static uint8_t	  StimerTaskId = 0;   //表示每个节点的标号 此后可以对外释放 方便开 和 关
static gtime_type *Stimerhead = NULL;  //链表的头结点


//遍历链表 周期loop执行
void gtimer_loop( void )
{
	gtime_type 	 *priv = Stimerhead;

	while( priv != NULL )
    {
        if( priv->start)
        {
            if( ++priv->cnt >= priv->time_out)
            {
                priv->cnt = 0;
                if(priv->fun != NULL)	priv->fun();
            }
        }
        priv = priv->next;      
	}
}


//关闭节点 《并没有链表移除 而是用标记位 优点：方便简单 缺点：内存无法释放》
uint8_t gtimer_stop_time(uint8_t handle)
{
	gtime_type *priv = Stimerhead;
	
	while( priv != NULL )
    {
        if( priv->handle == handle)
        {
            priv->start = false;
            return true;
        }
        priv = priv->next;     
	}  
    
    return false;
}
//开启节点 
uint8_t gtimer_start_time(uint8_t handle)
{
	gtime_type *priv = Stimerhead;
	
	while( priv != NULL )
    {
        if( priv->handle == handle)
        {
            priv->start = true;
            priv->cnt = 0;
            return true;
        }
        priv = priv->next;     
	}  
    
    return false;
}

//一个节点添加到链表 返回它的ID
uint8_t gtimer_register_isr( gtime_type *timenode, uint32_t time_out ,uint8_t start, time_call_back call_back)
{
	gtime_type *priv;
	gtime_type *this;

	this = timenode;//可以思考用malloc实现  目前这里和button一样我是自带内存
	
	this->cnt = 0;//实际计数值
	this->start = start;//开关
	this->handle = StimerTaskId++;//统一在链表中的ID
	this->time_out = time_out;//超时计数值
	this->fun = call_back;//节点逻辑函数
	this->next = NULL;//节点后继
	if( Stimerhead == NULL)
	{
		Stimerhead = this;//第一次 实例化head
	}
	else
	{
		priv = Stimerhead;
		while( priv->next != NULL )	priv = priv->next;//第一次以后：尾插
		priv->next = this;
	}    


    return (this->handle);
}


time_ops_type   gkTimer =
{
    .creat = gtimer_register_isr,
    .stop  = gtimer_stop_time , 
    .start = gtimer_start_time,
};
