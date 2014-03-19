#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include <SevenSegLED.h>
#include "LCD_Impl.h"

int GLB_Temperature_display_flag = 1;
int GLB_TiltAngle_RollPitch_display_flag = 1;

void LCD_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure_D;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	GPIO_StructInit(&GPIO_InitStructure_D);
	GPIO_InitStructure_D.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2  | GPIO_Pin_3 | GPIO_Pin_4  | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14;
	GPIO_InitStructure_D.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure_D.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_InitStructure_D.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure_D.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOD, &GPIO_InitStructure_D);
	
	GPIO_WriteBit (GPIOD, GPIO_Pin_8, Bit_SET);
}


void LCD_clear_display(void)
{
	    LCD_SelectRegs(LCD_REG_SEL_WRITE_COMMAND);
		  LCD_Command_dataRegs(LCD_CLEAR_DISPLAY);

			LCD_Pulse_Longer(5);
}

void LCD_display_CursorHome(void)
{
	
	    LCD_SelectRegs(LCD_REG_SEL_WRITE_COMMAND);
		  LCD_Command_dataRegs(LCD_CURSOR_HOME);
	
			LCD_Pulse(50000);
}

void LCD_CharacterEntryMode(void)
{
	
	    LCD_SelectRegs(LCD_REG_SEL_WRITE_COMMAND);
		  LCD_Command_dataRegs(LCD_CHAR_ENTRY_MODE);
	
	    LCD_Pulse(50000);
}

void LCD_FuncSet(void)
{
	    LCD_SelectRegs(LCD_REG_SEL_WRITE_COMMAND);
		  LCD_Command_dataRegs(LCD_FUNCTION_SET);
	
      LCD_Pulse(50000);
}


void LCD_DisplayOnOff(void)
{
	    LCD_SelectRegs(LCD_REG_SEL_WRITE_COMMAND);
		  LCD_Command_dataRegs(LCD_DISPLAY_ON_OFF);
	
      LCD_Pulse_Longer(1000);

}

void LCD_write(uint8_t num)
{
	LCD_SelectRegs(LCD_REG_SEL_WRITE_TEXT);    
	LCD_Command_dataRegs(num);

  LCD_Pulse(50000);

}

void LCD_set(uint8_t pos)
{

	LCD_SelectRegs(LCD_REG_SEL_WRITE_COMMAND);		
	LCD_Command_dataRegs(pos);
		
  LCD_Pulse(50000);
}


void LCD_Command_dataRegs(uint8_t data)
{
	int dataReg[LCD_DATA_REG_SIZE];
	uint8_t mask = 1;
	int i=0;
	
	while (i < LCD_DATA_REG_SIZE)
	{
		dataReg[i] = data & mask;
		mask = mask << 1;
		i++;
	}
	
	GPIO_WriteBit (GPIOD, GPIO_Pin_0, dataReg[0]);
	GPIO_WriteBit (GPIOD, GPIO_Pin_1, dataReg[1]);
	GPIO_WriteBit (GPIOD, GPIO_Pin_2, dataReg[2]);

	GPIO_WriteBit (GPIOD, GPIO_Pin_3, dataReg[3]);
	GPIO_WriteBit (GPIOD, GPIO_Pin_4, dataReg[4]);	
	GPIO_WriteBit (GPIOD, GPIO_Pin_5, dataReg[5]);

	GPIO_WriteBit (GPIOD, GPIO_Pin_6, dataReg[6]);	
	GPIO_WriteBit (GPIOD, GPIO_Pin_7, dataReg[7]);
	
	return;
	
}

// write text RegSel_RW --> 1 else 0 for write command
void LCD_SelectRegs(int RegSel_RW)
{
	if (RegSel_RW == LCD_REG_SEL_WRITE_COMMAND)
	{
			GPIO_WriteBit (GPIOD, GPIO_Pin_9, Bit_RESET);	
		  GPIO_WriteBit (GPIOD, GPIO_Pin_10, Bit_RESET);
	}
	else
	{
			GPIO_WriteBit (GPIOD, GPIO_Pin_9, Bit_RESET);	
		  GPIO_WriteBit (GPIOD, GPIO_Pin_10, Bit_SET);
	}
	return;
	
}


void LCD_Delay (uint32_t count)
{
	while (count)
	{
		count--;
	}
}

void LCD_Delay_Longer (uint32_t count)
{
	while (count)
	{
		LCD_Delay(50000);
		count--;
	}
}

void LCD_Pulse_Longer (uint32_t delay_longer)
{
		GPIO_WriteBit (GPIOD, GPIO_Pin_8, Bit_RESET);
		LCD_Delay_Longer(delay_longer);
		GPIO_WriteBit (GPIOD, GPIO_Pin_8, Bit_SET);
}

void LCD_Pulse (uint32_t delay)
{
		GPIO_WriteBit (GPIOD, GPIO_Pin_8, Bit_RESET);
		LCD_Delay(delay);
		GPIO_WriteBit (GPIOD, GPIO_Pin_8, Bit_SET);
}

void LCD_DisplayTemperature(float temperature)
{
	//init the array
	int temp[4] = {0, 0, 0, 0};
	int div = 10;
	int div_100 = 100;
	float ten=10.0;
	int temp_cast = 0;
	int buffer_size = 0, buffer_size_2 = 0;
	
//	int i=0;
	char buffer_temperature[LCD_DISPLAY_FIRST_LINE_SIZE];
	char buffer_temperatureDigitsSize[LCD_ONLY_TEMPERATURE_SIZE_IN_DIGITS];
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
		temp[2] = 10; // dot not required
		temp_cast = (int)temperature;
		temp[3] = (temperature - (float)temp_cast)*ten;
	
	}
	else
	{
		return;
	}
  //buffer_size = sprintf (buffer,"Temperature:%d%d.%d", temp[0], temp[1], temp[3]);
	if (GLB_Temperature_display_flag)
	{
		buffer_size = sprintf (buffer_temperature,"Temperature:");
		
		LCD_Delay_Longer(LCD_WAIT_BETWEEN_DISPLAY);
	  LCD_Display_String(buffer_temperature, buffer_size);
	  
		GLB_Temperature_display_flag--;
	}
	
	buffer_size_2 = sprintf (buffer_temperatureDigitsSize,"%d%d.%d", temp[0], temp[1], temp[3]);
	LCD_Delay_Longer(LCD_WAIT_BETWEEN_DISPLAY);
	LCD_DISPLAY_UPDATE_POS(0x8C, buffer_temperatureDigitsSize);
	//printf ("%s\n", buffer);
	
	return;
	
}

void LCD_Display_String(char* sentence, int sentenceSize)
{
	uint8_t i=0;
	
	LCD_clear_display();
	
	while(i < sentenceSize)
	{
		LCD_write(sentence[i]);
		i++;
	}
	return;
	
//		while(*sentence != '\0')
//	{
//		LCD_write(*sentence);
//		sentence++;
//	}
//	return;
	
}

void LCD_DISPLAY_UPDATE_POS(uint8_t pos, char* sentence)
{
	
	LCD_set(pos);
	
	while(*sentence != '\0')
	{
		LCD_write(*sentence);
		sentence++;
	}
	return;
	
}

void LCD_DisplayTiltAngle(float roll, float pitch)
{
	
	char dispRoll[] = "Roll:";
	char dispPitch[] = "Pitch:";
	char bufferRoll[9];
	char bufferPitch[9];
	
	sprintf(bufferRoll,"%f", roll);
	sprintf(bufferPitch,"%f", pitch);
	
//	//init the array for roll display
//	int32_t temp_roll[3] = {0, 0, 0};
//	int div = 10;
//	int32_t temp_cast_roll = (int32_t)roll;
//	
//	if (temp_cast_roll < 0)
//	{
//		temp_roll[0] = 11;  // Neg
//		temp_cast_roll = temp_cast_roll*(-1);
//	}
//	else
//	{
//		temp_roll[0] = 12;  // Pos
//	}
//	
//	
//	if (roll < 100)
//	{
//		temp_roll[1] = temp_cast_roll / div;
//		temp_roll[2] = temp_cast_roll - (temp_roll[1])*div;
//	}
//	else 
//	{
//		return;
//	}
//	
//		//init the array for pitch display
//	int32_t temp_pitch[3] = {0, 0, 0};
//	div = 10;
//	int32_t temp_cast_pitch = (int32_t)pitch;
//	
//	if (temp_cast_pitch < 0)
//	{
//		temp_pitch[0] = 11;  // Neg
//		temp_cast_pitch = temp_cast_pitch*(-1);
//	}
//	else
//	{
//		temp_pitch[0] = 12;  // Pos
//	}
//	
//	
//	if (pitch < 100)
//	{
//		temp_pitch[1] = temp_cast_pitch / div;
//		temp_pitch[2] = temp_cast_pitch - (temp_pitch[1])*div;
//	}
//	else 
//	{
//		return;
//	}
	
	if (GLB_TiltAngle_RollPitch_display_flag)
	{
		LCD_Delay_Longer(LCD_WAIT_BETWEEN_DISPLAY);
	  LCD_DISPLAY_UPDATE_POS(0x80, dispRoll);
		LCD_DISPLAY_UPDATE_POS(0xC0, dispPitch);
	  
		GLB_TiltAngle_RollPitch_display_flag--;
	}
	
	LCD_Delay_Longer(LCD_WAIT_BETWEEN_DISPLAY);
	LCD_DISPLAY_UPDATE_POS(0x85, bufferRoll);
	LCD_DISPLAY_UPDATE_POS(0xC6, bufferPitch);
	
}