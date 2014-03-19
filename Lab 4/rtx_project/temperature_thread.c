#include <stdio.h>
#include <stdlib.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_adc.h"
#include "core_cm4.h"
#include <cmsis_os.h>
#include <ADC_Impl.h>
#include <SevenSegLED.h>
#include "LCD_Impl.h"

/*!
 @brief Thread to perform detection of temperature 
 @param argument Unused
*/
void temperature_detection_thread(void const * argument);

// It may need some size of stack to store temperature.
//osThreadDef(temperature_detection_thread, osPriorityNormal, 1, 0);

void temperature_detection_thread (void const *argument) {
	/*Set configuration to ADC for acquiring Vadc*/
	set_ADC_config();
	
	/*Set configuration of LED display for testing purpose*/
	//LED_GPIO_Config();  ----->>>>>> No display
	
	uint16_t Vadc;
	float temp, Vsense, Vadc_filter, Vdd = 3.0, V25 = 0.76, frequency = 25;
	
	while(1){

		Vadc = get_ADC_temp();
		Vsense = Vdd * (float)Vadc / 4095;
		temp = (Vsense - V25)*(float)(1000/2.5) + (float)25;
		//DisplayTemperature(temp);
		LCD_DisplayTemperature(temp);
		//LCD_DisplayTiltAngle(temp, temp);
		/*Uncomment this line will break entire project*/
		//printf("The temperature: %f\n", temp);
	}
}