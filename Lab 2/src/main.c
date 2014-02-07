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
	uint16_t temperature;
	while(1) {

		//GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
		//printf("This is a TEST?");
		temperature = set_ADC_config();
		//if (temperature != 0)
		printf("The tesmperature %d\n", temperature);
	}
}




