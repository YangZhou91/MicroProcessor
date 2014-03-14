#include <stdio.h>
#include <stdlib.h>
#include "cmsis_os.h"

/*!
 @brief Thread to perform detection of tilts
 @param argument Unused
*/
void tilt_detection_thread(void const * argument);


osThreadDef(tilt_detection_thread, osPriorityNormal, 1, 0);