#include <stdio.h>
#include <stdlib.h>
#include "cmsis_os.h"

/*!
 @brief Thread to perform detection of tilt
 @param argument Unused
*/
void tilt_detection_thread(void const * argument);

void tilt_detection_thread(void const *argument) {
	while(1){
		osDelay(1000);
		//GPIOD->BSRRL = GPIO_Pin_12;
		//osDelay(1000);
		//GPIOD->BSRRH = GPIO_Pin_12;
		//printf("This is a thread \n");
	}
}