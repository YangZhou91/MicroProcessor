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

/*!
 @brief Thread to perform detection of tilt
 @param argument Unused
*/
void tilt_detection_thread(void const * argument);

void tilt_detection_thread(void const *argument) 
{
	
	float roll, pitch;
	int32_t raw_data[3] = {0,0,0};
	
	set_Accelerometer_MEM();
	Delay(100);
	
	MEM_Interrupt_Config();
	Delay(100);
	
	/*
	 * Create new filter struct object for filtering x, y and z and initialize
	 */
	
	// struct for filtering x
	int init_buffer = 0;               // index used to initialize the buffer
	InternalStateFilter_t newFilter_x;
	newFilter_x.newIndex = 0;
	newFilter_x.fullBuffer_flag = 0;
	while(init_buffer < FILTER_DEPTH)
	{
		newFilter_x.filterBuffer[init_buffer] = 0;
		init_buffer++;
	}
	
	// struct for filtering y	
	init_buffer = 0;  
	InternalStateFilter_t newFilter_y;
	newFilter_y.newIndex = 0;
	newFilter_y.fullBuffer_flag = 0;
	while(init_buffer < FILTER_DEPTH)
	{
		newFilter_y.filterBuffer[init_buffer] = 0;
		init_buffer++;
	}
	
	// struct for filtering z	
	init_buffer = 0;  
	InternalStateFilter_t newFilter_z;
	newFilter_z.newIndex = 0;
	newFilter_z.fullBuffer_flag = 0;
	while(init_buffer < FILTER_DEPTH)
	{
		newFilter_z.filterBuffer[init_buffer] = 0;
		init_buffer++;
	}
	
	while(1)
	{
		
//		if (Interrupt_Flag)
//		{
//				Interrupt_Flag=0;
//				LIS302DL_ReadACC(raw_data);   // read raw data
//			
//				//Filter out of noise from raw data
//				filtered_data[0] = MovingAverageFilter(&newFilter_x, raw_data[0]);
//				filtered_data[1] = MovingAverageFilter(&newFilter_y, raw_data[1]);
//				filtered_data[2] = MovingAverageFilter(&newFilter_z, raw_data[2]);
//				
//			  //Filter out of noise from raw data
//				get_calibration_data(filtered_data, calibrated_data);
//				
//			  // Calculate roll and pitch
//				roll = calculate_roll(calibrated_data);
//				pitch = calculate_pitch(calibrated_data);
//				
//				printf("Pitch: %f \t", pitch);
//				printf("Roll: %f \n", roll);
//				
//				//roll=45; --> for debug
//			  //pitch=45; --> for debug
//			
//				PWM_Display(roll);	
//			//PWM_Display(pitch);	 
//		}
	}
}