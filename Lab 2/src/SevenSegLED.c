#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx_adc.h"
#include "stm32f4xx.h"
#include <SevenSegLED.h>
/*
#define SEGMENT_1 3
#define SEGMENT_2 2
#define SEGMENT_3 1

#define SEGMENT_DELAY 0x430EB    //delay between corresponding segments
			
void SevenSegLED(int number,  int position);
void LED_GPIO_Config(void);
void Delay(uint32_t nCount);
void DisplayTemperature(float temperature);
void TURN_ON_OFF_PWM_LED(int flip);
*/

// Configure the LED port D for (Pins 0 -> 10)7-seg LEDs and alarm LED(pin 14)
void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure_D;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	GPIO_StructInit(&GPIO_InitStructure_D);
	GPIO_InitStructure_D.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2  | GPIO_Pin_3 | GPIO_Pin_4  | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14;
	GPIO_InitStructure_D.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure_D.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure_D.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure_D.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOD, &GPIO_InitStructure_D);
}

/*
 * Display number in position -> segment
 */
void SevenSegLED(int number,  int position)
{
	
	// reject out of bounds number and position
	if ((number < 0) || (number > 10) || (position < 1) || (position > 3))
		return;
	
	// Select line implementation
	if (position == SEGMENT_1)
	{
		GPIO_WriteBit(GPIOD, GPIO_Pin_8, Bit_SET);
		GPIO_WriteBit(GPIOD, GPIO_Pin_9, Bit_RESET);
		GPIO_WriteBit(GPIOD, GPIO_Pin_10, Bit_RESET);
	}
	else if (position == SEGMENT_2)
	{
		GPIO_WriteBit(GPIOD, GPIO_Pin_8, Bit_RESET);
		GPIO_WriteBit(GPIOD, GPIO_Pin_9, Bit_SET);
		GPIO_WriteBit(GPIOD, GPIO_Pin_10, Bit_RESET);
	}
	else
	{
		GPIO_WriteBit(GPIOD, GPIO_Pin_8, Bit_RESET);
		GPIO_WriteBit(GPIOD, GPIO_Pin_9, Bit_RESET);
		GPIO_WriteBit(GPIOD, GPIO_Pin_10, Bit_SET);
	}
	
	// Display number 0 -> 9 and dot
	switch(number)
	{
		case 0:
			GPIO_WriteBit (GPIOD, GPIO_Pin_0, Bit_SET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_1, Bit_SET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_2, Bit_SET);
		
			GPIO_WriteBit (GPIOD, GPIO_Pin_3, Bit_RESET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_4, Bit_SET);	
		  GPIO_WriteBit (GPIOD, GPIO_Pin_5, Bit_SET);
		
		  GPIO_WriteBit (GPIOD, GPIO_Pin_6, Bit_SET);	
		  GPIO_WriteBit (GPIOD, GPIO_Pin_7, Bit_RESET);
		
		
		  break;
		
		case 1:
			GPIO_WriteBit (GPIOD, GPIO_Pin_0, Bit_RESET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_1, Bit_RESET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_2, Bit_SET);
		
			GPIO_WriteBit (GPIOD, GPIO_Pin_3, Bit_RESET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_4, Bit_RESET);	
		  GPIO_WriteBit (GPIOD, GPIO_Pin_5, Bit_SET);
		
		  GPIO_WriteBit (GPIOD, GPIO_Pin_6, Bit_RESET);	
		  GPIO_WriteBit (GPIOD, GPIO_Pin_7, Bit_RESET);
		
		  break;
		
		case 2:
			GPIO_WriteBit (GPIOD, GPIO_Pin_0, Bit_RESET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_1, Bit_SET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_2, Bit_SET);
		
			GPIO_WriteBit (GPIOD, GPIO_Pin_3, Bit_SET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_4, Bit_SET);	
		  GPIO_WriteBit (GPIOD, GPIO_Pin_5, Bit_RESET);
		
		  GPIO_WriteBit (GPIOD, GPIO_Pin_6, Bit_SET);	
		  GPIO_WriteBit (GPIOD, GPIO_Pin_7, Bit_RESET);
		break;
		
		case 3:
			GPIO_WriteBit (GPIOD, GPIO_Pin_0, Bit_RESET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_1, Bit_SET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_2, Bit_SET);
		
			GPIO_WriteBit (GPIOD, GPIO_Pin_3, Bit_SET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_4, Bit_RESET);	
		  GPIO_WriteBit (GPIOD, GPIO_Pin_5, Bit_SET);
		
		  GPIO_WriteBit (GPIOD, GPIO_Pin_6, Bit_SET);	
		  GPIO_WriteBit (GPIOD, GPIO_Pin_7, Bit_RESET);
		break;
		
		case 4:
			GPIO_WriteBit (GPIOD, GPIO_Pin_0, Bit_SET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_1, Bit_RESET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_2, Bit_SET);
		
			GPIO_WriteBit (GPIOD, GPIO_Pin_3, Bit_SET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_4, Bit_RESET);	
		  GPIO_WriteBit (GPIOD, GPIO_Pin_5, Bit_SET);
		
		  GPIO_WriteBit (GPIOD, GPIO_Pin_6, Bit_RESET);	
		  GPIO_WriteBit (GPIOD, GPIO_Pin_7, Bit_RESET);
		break;
		
		case 5:
			GPIO_WriteBit (GPIOD, GPIO_Pin_0, Bit_SET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_1, Bit_SET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_2, Bit_RESET);
		
			GPIO_WriteBit (GPIOD, GPIO_Pin_3, Bit_SET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_4, Bit_RESET);	
		  GPIO_WriteBit (GPIOD, GPIO_Pin_5, Bit_SET);
		
		  GPIO_WriteBit (GPIOD, GPIO_Pin_6, Bit_SET);	
		  GPIO_WriteBit (GPIOD, GPIO_Pin_7, Bit_RESET);
		
		  break;
		
		case 6:
			GPIO_WriteBit (GPIOD, GPIO_Pin_0, Bit_SET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_1, Bit_SET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_2, Bit_RESET);
		
			GPIO_WriteBit (GPIOD, GPIO_Pin_3, Bit_SET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_4, Bit_SET);	
		  GPIO_WriteBit (GPIOD, GPIO_Pin_5, Bit_SET);
		
		  GPIO_WriteBit (GPIOD, GPIO_Pin_6, Bit_SET);	
		  GPIO_WriteBit (GPIOD, GPIO_Pin_7, Bit_RESET);
		
		  break;
		
		case 7:
			GPIO_WriteBit (GPIOD, GPIO_Pin_0, Bit_RESET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_1, Bit_SET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_2, Bit_SET);
		
			GPIO_WriteBit (GPIOD, GPIO_Pin_3, Bit_RESET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_4, Bit_RESET);	
		  GPIO_WriteBit (GPIOD, GPIO_Pin_5, Bit_SET);
		
		  GPIO_WriteBit (GPIOD, GPIO_Pin_6, Bit_RESET);	
		  GPIO_WriteBit (GPIOD, GPIO_Pin_7, Bit_RESET);
		
		  break;
		
		case 8:
			GPIO_WriteBit (GPIOD, GPIO_Pin_0, Bit_SET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_1, Bit_SET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_2, Bit_SET);
		
			GPIO_WriteBit (GPIOD, GPIO_Pin_3, Bit_SET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_4, Bit_SET);	
		  GPIO_WriteBit (GPIOD, GPIO_Pin_5, Bit_SET);
		
		  GPIO_WriteBit (GPIOD, GPIO_Pin_6, Bit_SET);	
		  GPIO_WriteBit (GPIOD, GPIO_Pin_7, Bit_RESET);
		
		  break;
		
		case 9:
			GPIO_WriteBit (GPIOD, GPIO_Pin_0, Bit_SET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_1, Bit_SET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_2, Bit_SET);
		
			GPIO_WriteBit (GPIOD, GPIO_Pin_3, Bit_SET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_4, Bit_RESET);	
		  GPIO_WriteBit (GPIOD, GPIO_Pin_5, Bit_SET);
		
		  GPIO_WriteBit (GPIOD, GPIO_Pin_6, Bit_SET);	
		  GPIO_WriteBit (GPIOD, GPIO_Pin_7, Bit_RESET);
		
		  break;
		
		//CASE 10 DOT
		case 10:
			GPIO_WriteBit (GPIOD, GPIO_Pin_0, Bit_RESET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_1, Bit_RESET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_2, Bit_RESET);
		
			GPIO_WriteBit (GPIOD, GPIO_Pin_3, Bit_RESET);
			GPIO_WriteBit (GPIOD, GPIO_Pin_4, Bit_RESET);	
		  GPIO_WriteBit (GPIOD, GPIO_Pin_5, Bit_RESET);
		
		  GPIO_WriteBit (GPIOD, GPIO_Pin_6, Bit_RESET);	
		  GPIO_WriteBit (GPIOD, GPIO_Pin_7, Bit_SET);
		
		  break;
		
		default:
			return;
	}
	
	return;
}

// Delay which acts like sleep
void Delay(uint32_t nCount) 
{
  while(nCount--);
}

//Display temperature 
void DisplayTemperature(float temperature)
{
	
	//init the array
	int temp[4] = {0, 0, 0, 0};
	int div = 10;
	int div_100 = 100;
	float ten=10.0;
	int temp_cast = 0;
	
	// reject less than zero temperature 
	if (temperature < 0)
	{
		printf("Tmeperature:%f is less then zero.\n", temperature);
		return;
	}
	
	if (temperature < 100)
	{
		temp[0] = (int)(temperature / div);
		temp[1] = (int)(temperature - (temp[0])*div);
		temp[2] = 10; // dot
		temp_cast = (int)temperature;
		temp[3] = (temperature - (float)temp_cast)*ten;
		
		SevenSegLED(temp[0], SEGMENT_1);
	  Delay(SEGMENT_DELAY);
	
		SevenSegLED(temp[1], SEGMENT_2);
		Delay(SEGMENT_DELAY);
		
		SevenSegLED(temp[2], SEGMENT_2);
		Delay(SEGMENT_DELAY);
	
		SevenSegLED(temp[3], SEGMENT_3);
	
	}
	else //if (temperature >= 100)
	{
		temp[0] = (int)(temperature / div_100);
		temp[1] = (int)((temperature - (temp[0])*div_100)/div);
		temp[2] = (float)temperature - ((temp[0])*div_100 + (temp[1])*div);
		
		SevenSegLED(temp[0], SEGMENT_1);
		Delay(SEGMENT_DELAY);
	
		SevenSegLED(temp[1], SEGMENT_2);
		Delay(SEGMENT_DELAY);
		
		SevenSegLED(temp[2], SEGMENT_3);
	
	}
	
	return;
	
}

// turns LED on and off
void TURN_ON_OFF_PWM_LED(int flip)
{
	GPIO_WriteBit(GPIOD, GPIO_Pin_14, flip);
}

void trigger_alarm(set_alarm_t* alarm)
{
	
	// decr -> 1 higher intensity to lower intensity
			if (alarm->decr_Flag)
			{
				while(alarm->count)
				{
					TURN_ON_OFF_PWM_LED(ALARM_ON);
					alarm->count--;
				}
				TURN_ON_OFF_PWM_LED(ALARM_OFF);
				Delay(alarm->Period - alarm->DutyCycle);
				alarm->dutyCycleAdjust -= alarm->width;
				alarm->count = alarm->dutyCycleAdjust;
				
				if (alarm->dutyCycleAdjust <= 0)
				{
					alarm->decr_Flag=0;
					alarm->incr_Flag=1;
					alarm->dutyCycleAdjust = alarm->width;
				}
			}
			
			// incr -> 1 lower intensity to higher intensity
			if (alarm->incr_Flag)
			{
				while(alarm->count <= alarm->dutyCycleAdjust)
				{
					TURN_ON_OFF_PWM_LED(ALARM_ON);
					alarm->count++;
				}
				TURN_ON_OFF_PWM_LED(ALARM_OFF);
				Delay(alarm->DutyCycle-alarm->dutyCycleAdjust);
				alarm->dutyCycleAdjust += alarm->width;
				alarm->count = 0;
				
				if (alarm->dutyCycleAdjust >= alarm->DutyCycle)
				{
					alarm->decr_Flag=1;
					alarm->incr_Flag=0;
					alarm->dutyCycleAdjust = alarm->DutyCycle;
					alarm->count = alarm->DutyCycle;
				}
			}
			
			return;
}
