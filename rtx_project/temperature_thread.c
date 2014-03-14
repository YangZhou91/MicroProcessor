#include <stdio.h>
#include <stdlib.h>
#include "cmsis_os.h"

/*!
 @brief Thread to perform detection of temperature 
 @param argument Unused
*/
void temperature_detection_thread(void const * argument);

// It may need some size of stack to store temperature.
//osThreadDef(temperature_detection_thread, osPriorityNormal, 1, 0);

void temperature_detection_thread (void const *argument) {
	while(1){
		osDelay(1000);
	}
}