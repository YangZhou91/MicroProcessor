#include <stdio.h>
#include <stdlib.h>
#include <cmsis_os.h>
#include <ADC_Impl.h>
#include <SevenSegLED.h>
/*!
 @brief Thread to perform detection of temperature 
 @param argument Unused
*/
void temperature_detection_thread(void const * argument);

// It may need some size of stack to store temperature.
//osThreadDef(temperature_detection_thread, osPriorityNormal, 1, 0);

void temperature_detection_thread (void const *argument) {
	/*Set configuration */
	set_ADC_config();
	uint16_t Vadc;
	float temp, Vsense, Vadc_filter, Vdd = 3.0, V25 = 0.76, frequency = 25;
	
	while(1){
		osDelay(1000);
		
		Vadc = get_ADC_temp();
		Vsense = Vdd * (float)Vadc / 4095;
		temp = (Vsense - V25)*(float)(1000/2.5) + (float)25;
		//printf("The temperature: %f\n", temp);
	}
}