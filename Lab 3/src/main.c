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

#define PI 3.14159265
//NOTE TO STUDENTS: Uncomment the version of drivers related to your sensor
//#include "lis3dsh.h"
#include "stm32f4_discovery_lis302dl.h"

int main()
{
		
	int32_t raw_data[3];
	float calibrated_data[3] = {0, 0, 0};
	
	set_Accelerometer_MEM();
	
	/*
	 * Create new filter struct object for filtering and initialize
	 */
	int init_buffer = 0;               // init the buffer
	InternalStateFilter_t newFilter;
	newFilter.newIndex = 0;
	newFilter.fullBuffer_flag = 0;
	while(init_buffer < FILTER_DEPTH)
	{
		newFilter.filterBuffer[init_buffer] = 0;
		init_buffer++;
	}
	while(1)
	{

		LIS302DL_ReadACC(raw_data);
		/*Filter out of noise from raw data*/
		MovingAverageFilter(&newFilter, raw_data[0]);
		MovingAverageFilter(&newFilter, raw_data[1]);
		MovingAverageFilter(&newFilter, raw_data[2]);
		
		get_calibration_data(raw_data, calibrated_data);
		float roll = calculate_roll(calibrated_data);
		float pitch = calculate_pitch(calibrated_data);
		/*
		printf("x: %f \t",calibrated_data[0]);
		printf("y: %f \t",calibrated_data[1]);
		printf("z: %f \n",calibrated_data[2]);
		*/
		printf("Pitch: %f \t", pitch);
		printf("Roll: %f \n", roll);
	}
	
	return 0;
}







