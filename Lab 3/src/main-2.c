#include <stdio.h>
#include <stdlib.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "math.h"
#include "atan_LUT.h"
#include "accelerometer_conf.h"
#include "calibration.h"
#include "tilt_angle_calculation.h"
#include "MovingAverageFilter.h"
#include <MEM_Interrupt.h>
#include "PWM_Servo_Impl.h"
#include <LED_Tim_Interrupt.h>
#include "stm32f4_discovery_lis302dl.h"
#include <SevenSegLED.h>

#define WAIT_ON_RESET 750

//void Delay(uint64_t count);

static volatile uint_fast16_t Interrupt_Flag, Interrupt_Timer_LED;
static float roll, pitch;
static int reset_flag=1;
static uint8_t DisplayInSegment=1;

int main()


{
	int32_t raw_data[3] = {0, 0, 0};
	int32_t filtered_data[3] = {0, 0, 0};
	reset_flag=1;
	int waitOnReset = WAIT_ON_RESET;
	float calibrated_data[3] = {0, 0, 0};
	float offset_roll = 0, offset_pitch;
	roll=0, pitch=0;
	
	set_Accelerometer_MEM();
	Delay(100);
	
	MEM_Interrupt_Config();
	Delay(100);
	
	EXTI_NVIC_Config();
	Delay(100);
	PWM_Servo_config();
	
	LED_Tim_Interrupt();
	
	LED_GPIO_Config();
	
	Interrupt_Timer_LED=1;
	
	/*
	float disp=18;
	while(1)
	{
		DisplayTemperature(disp);
	}
	*/
	
	if (reset_flag)
	{
		printf("Pitch: %f \t", pitch);
		printf("Roll: %f \n", roll);
		while (waitOnReset)
		{
			Delay(50000);
			waitOnReset--;
			PWM_Test(roll);
			DisplayAngle(roll, 3);
		}
		 reset_flag=0;	
	}
	
	/*
	 * Create new filter struct object for filtering and initialize
	 */
	int init_buffer = 0;               // init the buffer
	InternalStateFilter_t newFilter_x;
	newFilter_x.newIndex = 0;
	newFilter_x.fullBuffer_flag = 0;
	while(init_buffer < FILTER_DEPTH)
	{
		newFilter_x.filterBuffer[init_buffer] = 0;
		init_buffer++;
	}
	
	init_buffer = 0;  
	InternalStateFilter_t newFilter_y;
	newFilter_y.newIndex = 0;
	newFilter_y.fullBuffer_flag = 0;
	while(init_buffer < FILTER_DEPTH)
	{
		newFilter_y.filterBuffer[init_buffer] = 0;
		init_buffer++;
	}
	
	init_buffer = 0;  
	InternalStateFilter_t newFilter_z;
	newFilter_z.newIndex = 0;
	newFilter_z.fullBuffer_flag = 0;
	while(init_buffer < FILTER_DEPTH)
	{
		newFilter_z.filterBuffer[init_buffer] = 0;
		init_buffer++;
	}
	
	Interrupt_Flag = 1;
	while(1)
	{
		if (Interrupt_Flag)
		{
				Interrupt_Flag=0;
				LIS302DL_ReadACC(raw_data);
				//Filter out of noise from raw data
				filtered_data[0] = MovingAverageFilter(&newFilter_x, raw_data[0]);
				filtered_data[1] = MovingAverageFilter(&newFilter_y, raw_data[1]);
				filtered_data[2] = MovingAverageFilter(&newFilter_z, raw_data[2]);
				
				get_calibration_data(filtered_data, calibrated_data);
				//printf("x_r: %d ", raw_data[0]);
				//printf("y_r: %d ", raw_data[1]);
				//printf("z_r: %d \n", raw_data[2]);
				
				//printf("x_fil: %d \t", filtered_data[0]);
				//printf("y_fil: %d \t", filtered_data[1]);
				//printf("z_c: %f \n", calibrated_data[2]);
				
				roll = calculate_roll(calibrated_data) + offset_roll;
				pitch = calculate_pitch(calibrated_data);
				
				printf("Pitch: %f \t", pitch);
				printf("Roll: %f \n", roll);
				
				//roll=45; --> for debug
				PWM_Test(roll);	
		}
		
		if (Interrupt_Timer_LED)
		{
			 DisplayAngle(roll, DisplayInSegment);
			 DisplayInSegment++;
			 if (DisplayInSegment == 4)
			 {
				 DisplayInSegment=1;
			 }
			 Interrupt_Timer_LED=0;
		}
	
   }
	return 0;

}

void EXTI0_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  {

    Interrupt_Flag = 1;
    //printf("Interrupt\n");
		
    /* Clear the EXTI line 0 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line0);
  }
}
/*
void Delay(uint64_t count)
{
	while(count)
	{
		count--;
	}
}
*/
void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
  {
		//printf("TIMER Interrupt\n");
		Interrupt_Timer_LED=1;
     TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
  }
}




