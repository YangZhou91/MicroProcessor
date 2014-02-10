#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
// include the ADC driver.
#include "stm32f4xx_adc.h"
#include "ADC_config.h"
#include "ADC_temp.h"
// include the SysTick Config
#include "core_cm4.h"
//#include "gpio_example.h"
	
static volatile uint_fast16_t ticks;

int main()
{
  set_ADC_config();
	int test = 0;
	//GPIO_example_config();
	uint16_t Vadc;
	float temp, Vsense;	
	float Vdd = 3;
	float V25 = 0.76;
	float frequency = 25;
	ticks = 0;
	// Configure for 10ms period
	// Note: argument here must be less than 0xFFFFF;  //(24 bit timer)
	// At 168MHz, this just a bit slower than 100Hz
	SysTick_Config(1 / frequency * SystemCoreClock);
	
	while(1) {
		
		// Wait for an interrupt
		while(!ticks);
		
		// Decrement ticks
		ticks = 0;
		
		Vadc = get_ADC_temp();
		Vsense = Vdd * Vadc / 4095;
		temp = (Vsense - V25)*1000/2.5 + 25;
		printf("The tesmperature %f\n", temp);
	}
}

void SysTick_Handler(){
	ticks = 1;
}



