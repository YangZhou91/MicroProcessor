#include <stdio.h>
#include <stdlib.h>
#include "cmsis_os.h"
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include <accelerometer_conf.h>
#include <stm32f4_discovery_lis302dl.h>
#include "accelerometer_conf.h"
#include "calibration.h"
#include "tilt_angle_calculation.h"
#include "MovingAverageFilter.h"
#include <MEM_Interrupt.h>
#include <SevenSegLED.h>
#include "math.h"
#include "LCD_Impl.h"

/*!
 @brief Thread to perform detection of tilt
 @param argument Unused
*/
void tilt_detection_thread(void const * argument);

static volatile uint_fast16_t Interrupt_Flag, Interrupt_Timer_LED;
static float roll, pitch;
static int reset_flag=1;
static uint8_t DisplayInSegment=1;

void tilt_detection_thread(void const *argument) 
{
	
	//float roll, pitch;
	int32_t raw_data[3] = {0,0,0};
	float calibrated_data[3] = {0,0,0};
	reset_flag = 1;
	roll = 0, pitch = 0;
	/*Add calibration and filter later on*/
	set_Accelerometer_MEM();
	Delay(100);
	
	MEM_Interrupt_Config();
	Delay(100);
	
	EXTI_NVIC_Config();
	Delay(100);
	
	Interrupt_Flag = 1;
	while(1)
	{
		
			if (Interrupt_Flag)
			{
					Interrupt_Flag=0;
					LIS302DL_ReadACC(raw_data);   // read raw data
			
//				//Filter out of noise from raw data
//				filtered_data[0] = MovingAverageFilter(&newFilter_x, raw_data[0]);
//				filtered_data[1] = MovingAverageFilter(&newFilter_y, raw_data[1]);
//				filtered_data[2] = MovingAverageFilter(&newFilter_z, raw_data[2]);
//				
//			  //Filter out of noise from raw data
				get_calibration_data(raw_data, calibrated_data);
//				
//			  // Calculate roll and pitch
				roll = calculate_roll(calibrated_data);
				pitch = calculate_pitch(calibrated_data);
//				
				LCD_DisplayTiltAngle(roll, pitch);
//				printf("Pitch: %f \t", pitch);
//			printf("Roll: %f \n", roll);
//				
//				//roll=45; --> for debug
//			  //pitch=45; --> for debug
//			
//				PWM_Display(roll);	
//			//PWM_Display(pitch);	 
		}
	}
}

void EXTI1_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line1) != RESET)
  {

    Interrupt_Flag = 1;
    //printf("Interrupt\n");

    /* Clear the EXTI line 0 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line1);
  }
}

