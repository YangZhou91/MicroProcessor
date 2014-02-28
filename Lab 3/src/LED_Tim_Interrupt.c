#include <stdint.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_exti.h"
#include "stm32f4_discovery_lis302dl.h"
#include "misc.h"
#include "PWM_Servo_Impl.h"
#include <LED_Tim_Interrupt.h>


void LED_Tim_Interrupt(void)
{
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    TIM_TimeBaseInitTypeDef timerInitStructure;
	
    timerInitStructure.TIM_Prescaler = 4000;
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period = 5;
    timerInitStructure.TIM_ClockDivision = 0;
   // timerInitStructure.TIM_RepetitionCounter = 0;
	
    TIM_TimeBaseInit(TIM4, &timerInitStructure);
	
	  /* TIM Interrupts enable */
    TIM_ITConfig(TIM4,TIM_IT_Update, ENABLE);
	
    TIM_Cmd(TIM4, ENABLE);
	
	  NVIC_InitTypeDef nvicStructure;
	
    nvicStructure.NVIC_IRQChannel = TIM4_IRQn;
    nvicStructure.NVIC_IRQChannelPreemptionPriority = 1;
    nvicStructure.NVIC_IRQChannelSubPriority = 1;
	
    nvicStructure.NVIC_IRQChannelCmd = ENABLE;
		
    NVIC_Init(&nvicStructure);
	
	  return;
	
}

























