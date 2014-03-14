#include <stdio.h>
#include <stdlib.h>
#include "cmsis_os.h"
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include <accelerometer_conf.h>
#include <stm32f4_discovery_lis302dl.h>
/*!
 @brief Thread to perform detection of tilt
 @param argument Unused
*/
void tilt_detection_thread(void const * argument);

void tilt_detection_thread(void const *argument) {
	
	float roll, pitch;
	int32_t raw_data[3] = {0,0,0};
	
	set_Accelerometer_MEM();
	while(1){
		
		//GPIOD->BSRRL = GPIO_Pin_12;
		//osDelay(1000);
		//GPIOD->BSRRH = GPIO_Pin_12;
		//printf("This is a thread \n");
	}
}