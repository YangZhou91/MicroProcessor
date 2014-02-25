#include "stm32f4_discovery_lis302dl.h"
#include "accelerometer_conf.h"
#include <stdint.h>


/**
	* @brief Set up configuration for Accelerometer 
	* @param void
	*
	*/
	void set_Accelerometer_MEM(void)
	{
			LIS302DL_InitTypeDef LIS302DL_InitStruct;
			
		/* Set configuration for LIS302DL*/
			LIS302DL_InitStruct.Power_Mode = LIS302DL_LOWPOWERMODE_ACTIVE;
		/* Set the sampling frequency as 100Hz*/
			LIS302DL_InitStruct.Output_DataRate = LIS302DL_DATARATE_100;
		/* Enable X, Y, Z axes*/
			LIS302DL_InitStruct.Axes_Enable = LIS302DL_XYZ_ENABLE;
		/* Set the range to +/- 2.0g */
			LIS302DL_InitStruct.Full_Scale = LIS302DL_FULLSCALE_2_3;
		/* Set the self-test*/
			LIS302DL_InitStruct.Self_Test = LIS302DL_SELFTEST_NORMAL;
			LIS302DL_Init(&LIS302DL_InitStruct);

	}
	
	/**
		* @brief Retrieve data from Accelerometer
		* @param void
		*/

	void LIS302DL_ReadACC(int32_t *output_Accelerometer);
		

	