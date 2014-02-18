  /*******************************************************************
  * @file    main.c
  * @author  Tashreef Anowar, Yang Zhou
  * @date    17-February-2014
  * @brief   This file provides the main method for Lab 2.
	********************************************************************/

#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_adc.h"
#include "core_cm4.h"
#include <SevenSegLED.h>
#include <MovingAverageFilter.h>
#include <ADC_Impl.h>

static volatile uint_fast16_t ticks;

//ALARM THRESHOLD
float Alarm_Upper_Limit = 25.0;

int main()
{
	//Init ADC
  set_ADC_config();
	
	uint16_t Vadc;
	float temp, Vsense, Vadc_filter, Vdd = 3.0, V25 = 0.76, frequency = 25;	
	ticks = 0;                 // ticks for interrupt 
	
	LED_GPIO_Config();         // Init the LEDs for Alarm and seven seg-display
	
	// DEBUG PURPOSE: TEST SINGLE SEGMENT
	//while(1)
  //DisplayTemperature(20.0);
	
	/*
	 * Create new filter struct object for filtering and initialize
	 */
	int init_buffer = 0;               // init the buffer
	InternalStateFilter_t newFilter;
	newFilter.newIndex = 0;
	newFilter.fullBuffer_flag = 0;
	while(init_buffer < FILTER_DEPTH)
	{
		newFilter.filterBuffer[init_buffer] = 0;
		init_buffer++;
	}
	
	// ALARM PWM configurations 
  // incr and decr are flags for incrementing and decrementing the PWM counter
  // increments from 0 -> lowerlim with LED on and delay with upperlim-lowerlim with LED off
	// adjust width 
	
	set_alarm_t newAlarm;
	
	newAlarm.Period = 40000;
	newAlarm.DutyCycle = 24000;
	newAlarm.dutyCycleAdjust = newAlarm.DutyCycle;
	newAlarm.incr_Flag = 0;
	newAlarm.decr_Flag = 1;
	newAlarm.count = newAlarm.DutyCycle;
	newAlarm.width = 1000;
	
	// PREPARE SYSTICK Interrupt
	// Configure for 10ms period
	// Note: argument here must be less than 0xFFFFF;  //(24 bit timer)
	// At 168MHz, this just a bit slower than 100Hz
	SysTick_Config(1 / frequency * SystemCoreClock);
	 
	while(1) 
	{
		
		// Wait for an interrupt
		while(!ticks);
		
		// Decrement ticks
		ticks = 0;
		
		Vadc = get_ADC_temp();
		Vadc_filter = MovingAverageFilter(&newFilter, Vadc);
		
		Vsense = Vdd * (float)Vadc_filter / 4095;
		temp = (Vsense - V25)*(float)(1000/2.5) + (float)25;
		DisplayTemperature(temp);
		
		// CHECK for ALARM
		if ((temp > Alarm_Upper_Limit) && ALARM_ON)
		{
			trigger_alarm(&newAlarm);
		}
		else
		{
			TURN_ON_OFF_PWM_LED(ALARM_OFF);
		}
		printf("The temperature: %f, filtered_volt: %f\n", temp, Vadc_filter);
	}
}

void SysTick_Handler(){
	ticks = 1;
}

