#include "motor.h"
#include "tim.h"
//方向
#define STEPMOTOR_DIR_FORWARD()               HAL_GPIO_WritePin(M_DIR_GPIO_Port,M_DIR_Pin,GPIO_PIN_RESET)
#define STEPMOTOR_DIR_REVERSAL()              HAL_GPIO_WritePin(M_DIR_GPIO_Port,M_DIR_Pin,GPIO_PIN_SET)
//开关 因为共阳外接5V这里是0就停机
#define STEPMOTOR_OUTPUT_ENABLE()             HAL_GPIO_WritePin(M_ENV_GPIO_Port,M_ENV_Pin,GPIO_PIN_SET)//开机
#define STEPMOTOR_OUTPUT_DISABLE()            HAL_GPIO_WritePin(M_ENV_GPIO_Port,M_ENV_Pin,GPIO_PIN_RESET)//停机


void motor_left(void) {STEPMOTOR_DIR_FORWARD();};
void motor_right(void){STEPMOTOR_DIR_REVERSAL();};
void motor_on(void) {HAL_TIM_OC_Start_IT(&htim1,TIM_CHANNEL_1);STEPMOTOR_OUTPUT_ENABLE();};
void motor_off(void){HAL_TIM_OC_Stop_IT(&htim1,TIM_CHANNEL_1); };//STEPMOTOR_OUTPUT_DISABLE();};

//下面函数 进2次 是一个完整脉冲
__IO uint16_t Toggle_Pulse=200;//1000不动 500动了
__IO uint32_t numtogive;
void setnumtogive(char a){numtogive = 800*a;motor_on();};
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
#if 0    
  uint16_t count;
  count=__HAL_TIM_GET_COUNTER(&htim1);
  __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,count+Toggle_Pulse);
#else

    if(numtogive == 0) 
    {
       // printf("886\r\n");
        motor_off();
        return;
    }
    --numtogive;
   // printf("ing\r\n");
  __HAL_TIM_SET_COUNTER(&htim1,0);
  __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,Toggle_Pulse);
#endif    
}