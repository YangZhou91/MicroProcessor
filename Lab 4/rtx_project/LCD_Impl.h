
extern int GLB_Temperature_display_flag;
extern int GLB_TiltAngle_RollPitch_display_flag;

#define LCD_DATA_REG_SIZE 8

#define LCD_REG_SEL_WRITE_COMMAND 0
#define LCD_REG_SEL_WRITE_TEXT 1

#define LCD_DISPLAY_FIRST_LINE_SIZE 16
#define LCD_WAIT_BETWEEN_DISPLAY 200
#define LCD_ONLY_TEMPERATURE_SIZE_IN_DIGITS 5

// LCD Commands
#define LCD_CLEAR_DISPLAY 	0x01
#define LCD_CHAR_ENTRY_MODE 0x06
#define LCD_CURSOR_HOME 		0x02
#define LCD_FUNCTION_SET 		0x38
#define LCD_SET 						0x80
#define LCD_DISPLAY_ON_OFF  0x0F

//typedef enum 
//	{
//		write,
//		read
//	}LCD_SelectReg_mode_t;

void LCD_GPIO_Config(void);
void LCD_clear_display(void);
void LCD_DisplayOnOff(void);
void LCD_FuncSet(void);
void LCD_CharacterEntryMode(void);
void LCD_display_CursorHome(void);
void LCD_write(uint8_t num);
void LCD_set(uint8_t pos);
void LCD_Command_dataRegs(uint8_t data);
void LCD_SelectRegs(int RegSel_RW);
void LCD_Delay_Longer(uint32_t count);
void LCD_Delay(uint32_t count);
void LCD_Pulse (uint32_t delay);
void LCD_Pulse_Longer (uint32_t delay_longer);
void LCD_DisplayTemperature(float temperature);
void LCD_Display_String(char* sentence, int sentenceSize);
void LCD_DISPLAY_UPDATE_POS(uint8_t pos, char* sentence);
void LCD_DisplayTiltAngle(float roll, float pitch);

