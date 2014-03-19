#include <stdio.h>
#include <stdlib.h>
#include "arm_math.h"
#include "stm32f4xx.h"
#include "cmsis_os.h"
#include "stm32f4_discovery_lis302dl.h"
#include "temperature_thread.h"
#include "tilt_thread.h"
#include "LCD_Impl.h"
#include <SevenSegLED.h>

//static volatile uint_fast16_t Interrupt_Flag, Interrupt_Timer_LED;

/*!
 @brief Thread to perform menial tasks such as switching LEDs
 @param argument Unused
 */
void thread(void const * argument);

//! Thread structure for above thread
osThreadDef(thread, osPriorityNormal, 1, 0);
osThreadDef(temperature_detection_thread, osPriorityNormal, 1, 0);
osThreadDef(tilt_detection_thread, osPriorityNormal, 1, 0);
/*!
 @brief Program entry point
 */
int main (void) {
	// ID for thread
	osThreadId tid_thread1;
	osThreadId temperature_thread;
	osThreadId tilt_thread;
	
	/* This TypeDef is a structure defined in the
	 * ST's library and it contains all the properties
	 * the corresponding peripheral has, such as output mode,
	 * pullup / pulldown resistors etc.
	 * 
	 * These structures are defined for every peripheral so 
	 * every peripheral has it's own TypeDef. The good news is
	 * they always work the same so once you've got a hang
	 * of it you can initialize any peripheral.
	 * 
	 * The properties of the periperals can be found in the corresponding
	 * header file e.g. stm32f4xx_gpio.h and the source file stm32f4xx_gpio.c
	 */
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	
	/* This enables the peripheral clock to 
	 * the GPIOA IO module
	 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	/* Here the GPIOA module is initialized.
	 * We want to use PA0 as an input because
	 * the USER button on the board is connected
	 * between this pin and VCC.
	 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;		  // we want to configure PA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 	  // we want it to be an input
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//this sets the GPIO modules clock speed
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;   // this sets the pin type to push / pull (as opposed to open drain)
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;   // this enables the pulldown resistor --> we want to detect a high level
	GPIO_Init(GPIOA, &GPIO_InitStructure);			  // this passes the configuration to the Init function which takes care of the low level stuff

	LCD_GPIO_Config();
	Delay(50000);
	LCD_FuncSet();
	Delay(50000);
	Delay(50000);
	
	LCD_DisplayOnOff();
	//Delay(50000);
	
	
	LCD_clear_display();

	LCD_display_CursorHome(); //--> once after initialize to point to position 01
	LCD_CharacterEntryMode(); //--> increments cursor

	LCD_write(75); // --> writes
  LCD_write(86);

  LCD_clear_display();
  //LCD_DisplayTiltAngle(22, 22);
	LCD_write(80); // --> writes
  LCD_write(100);
	
	// Start thread
	tid_thread1 = osThreadCreate(osThread(thread), NULL);
	temperature_thread = osThreadCreate(osThread(temperature_detection_thread),NULL);	tilt_thread = osThreadCreate(osThread(tilt_detection_thread),NULL);
	// The below doesn't really need to be in a loop
	while(1){
		osDelay(1000);
		//osDelay(osWaitForever);
		/* Every GPIO port has an input and 
		 * output data register, ODR and IDR 
		 * respectively, which hold the status of the pin
		 * 
		 * Here the IDR of GPIOA is checked whether bit 0 is
		 * set or not. If it's set the button is pressed
		 */
		if(GPIOA->IDR & 0x0001){
				printf("The user button has been pressed.\n");
		}
	}
}

// thread function 'thread'
void thread (void const *argument) {
	while(1){
		osDelay(1000);
		GPIOD->BSRRL = GPIO_Pin_12;
		osDelay(1000);
		GPIOD->BSRRH = GPIO_Pin_12;
		//printf("This is a thread \n");
	}
}
