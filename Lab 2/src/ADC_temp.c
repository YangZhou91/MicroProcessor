#include "ADC_temp.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx.h"

uint16_t get_ADC_temp(){
		
		ADC_SoftwareStartConv(ADC1);
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
		ADC_GetConversionValue(ADC1);
		ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
		uint16_t temperature = ADC_GetConversionValue(ADC1);
		return temperature;
}