
#include <stdint.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_exti.h"
#include "stm32f4_discovery_lis302dl.h"
#include "misc.h"


void EXTI_NVIC_Config(void)
{
	GPIO_InitTypeDef GPIO_MEM_Init_struct;
	EXTI_InitTypeDef EXTI_MEM_struct;
	NVIC_InitTypeDef NVIC_MEM_struct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	// Enable SYSCFG clock 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	GPIO_StructInit(&GPIO_MEM_Init_struct);
	
	GPIO_MEM_Init_struct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_MEM_Init_struct.GPIO_Pin = GPIO_Pin_0;
	GPIO_MEM_Init_struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  /*
	GPIO_MEM_Init_struct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_MEM_Init_struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_MEM_Init_struct.GPIO_Pin = GPIO_Pin_0;
  //GPIO_Init(GPIOA, &GPIO_MEM_Init_struct);
		*/
	GPIO_Init(GPIOE, &GPIO_MEM_Init_struct);
	GPIO_Init(GPIOA, &GPIO_MEM_Init_struct);
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource0);
	
	EXTI_MEM_struct.EXTI_Line = EXTI_Line0;
  EXTI_MEM_struct.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_MEM_struct.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_MEM_struct.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_MEM_struct);

  /* Enable and set EXTI Line0 Interrupt to the lowest priority */
  NVIC_MEM_struct.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_MEM_struct.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_MEM_struct.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_MEM_struct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_MEM_struct);
	
	return;

}


void MEM_Interrupt_Config(void)
{
	
  
  
  LIS302DL_InterruptConfigTypeDef LIS302DL_InterruptStruct;  
  
  /* SysTick end of count event each 10ms */
 // SysTick_Config(SystemCoreClock/ 100);
    
  /* Set configuration of Internal High Pass Filter of LIS302DL*/
  LIS302DL_InterruptStruct.Latch_Request = LIS302DL_INTERRUPTREQUEST_NOTLATCHED;
  LIS302DL_InterruptStruct.SingleClick_Axes = LIS302DL_CLICKINTERRUPT_XYZ_DISABLE;
  LIS302DL_InterruptStruct.DoubleClick_Axes = LIS302DL_CLICKINTERRUPT_XYZ_DISABLE;
	
  LIS302DL_InterruptConfig(&LIS302DL_InterruptStruct);

  /* Required delay for the MEMS Accelerometre: Turn-on time = 3/Output data Rate 
                                                             = 3/100 = 30ms */
  
  /* Configure Interrupt control register: enable Click interrupt1 */
  uint8_t ctrl = 0;
	ctrl = 0x4;
	
	LIS302DL_Write(&ctrl, LIS302DL_CTRL_REG3_ADDR, 1);
	
	return;

}
 
