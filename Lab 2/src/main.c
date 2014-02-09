#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
// include the ADC driver.
#include "stm32f4xx_adc.h"
#include "ADC_config.h"
//#include "gpio_example.h"


int main()
{
	int test = 0;
	//GPIO_example_config();
	uint16_t Vref;
	float temp, Vsense;	
	float Vdd = 3;
	float V25 = 0.76;
	while(1) {

		Vref = set_ADC_config();
		Vsense = Vdd * Vref / 4095;
		temp = (Vsense - V25)*1000/2.5 + 25;
		printf("The tesmperature %f\n", temp);
	}
}




