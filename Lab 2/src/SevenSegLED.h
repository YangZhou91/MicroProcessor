#define SEGMENT_1 3
#define SEGMENT_2 2
#define SEGMENT_3 1

#define SEGMENT_DELAY 0x430EB    //delay between corresponding segments
	
typedef struct SET_ALARM
{
	int Period;
	int DutyCycle;
	int dutyCycleAdjust;
	int incr_Flag;
	int decr_Flag;
	int count;
	int width;
} set_alarm_t;


enum {
	 ALARM_OFF = 0,
	 ALARM_ON
};


void SevenSegLED(int number,  int position);
void LED_GPIO_Config(void);
void Delay(uint32_t nCount);
void DisplayTemperature(float temperature);
void TURN_ON_OFF_PWM_LED(int flip);
void trigger_alarm(set_alarm_t* alarm);


/*

int upperlim=40000, lowerlim=24000, period, incr=0, decr=1, count, width=500;
	period = lowerlim;
	count = lowerlim;

// LED Segments
#define SEGMENT_1 3
#define SEGMENT_2 2
#define SEGMENT_3 1

#define DISPLAY_0                                 \
			GPIO_WriteBit (GPIOD, GPIO_Pin_0, Bit_SET); \
			GPIO_WriteBit (GPIOD, GPIO_Pin_1, Bit_SET); \
			GPIO_WriteBit (GPIOD, GPIO_Pin_2, Bit_SET); \
		                                              \
			GPIO_WriteBit (GPIOD, GPIO_Pin_3, Bit_RESET); \
			GPIO_WriteBit (GPIOD, GPIO_Pin_4, Bit_SET);	  \
		  GPIO_WriteBit (GPIOD, GPIO_Pin_5, Bit_SET);	  \
		                                                \
		  GPIO_WriteBit (GPIOD, GPIO_Pin_6, Bit_SET);	  \
		  GPIO_WriteBit (GPIOD, GPIO_Pin_7, Bit_RESET); 
		
#define DISPLAY_1 																	\
			GPIO_WriteBit (GPIOD, GPIO_Pin_0, Bit_RESET); \
			GPIO_WriteBit (GPIOD, GPIO_Pin_1, Bit_RESET); \
			GPIO_WriteBit (GPIOD, GPIO_Pin_2, Bit_SET);   \
		                                                \
			GPIO_WriteBit (GPIOD, GPIO_Pin_3, Bit_RESET); \
			GPIO_WriteBit (GPIOD, GPIO_Pin_4, Bit_RESET);	\
		  GPIO_WriteBit (GPIOD, GPIO_Pin_5, Bit_SET);   \
		                                                \
		  GPIO_WriteBit (GPIOD, GPIO_Pin_6, Bit_RESET);	\
		  GPIO_WriteBit (GPIOD, GPIO_Pin_7, Bit_RESET); 
		
		
#define DISPLAY_2                                   \
			GPIO_WriteBit (GPIOD, GPIO_Pin_0, Bit_RESET); \
			GPIO_WriteBit (GPIOD, GPIO_Pin_1, Bit_SET);   \
			GPIO_WriteBit (GPIOD, GPIO_Pin_2, Bit_SET);   \
		                                                \
			GPIO_WriteBit (GPIOD, GPIO_Pin_3, Bit_SET);   \
			GPIO_WriteBit (GPIOD, GPIO_Pin_4, Bit_SET);	  \
		  GPIO_WriteBit (GPIOD, GPIO_Pin_5, Bit_RESET); \
		                                                \
		  GPIO_WriteBit (GPIOD, GPIO_Pin_6, Bit_SET);	  \
		  GPIO_WriteBit (GPIOD, GPIO_Pin_7, Bit_RESET); 
		
#define DISPLAY_3                                   \
			GPIO_WriteBit (GPIOD, GPIO_Pin_0, Bit_RESET); \
			GPIO_WriteBit (GPIOD, GPIO_Pin_1, Bit_SET);   \
			GPIO_WriteBit (GPIOD, GPIO_Pin_2, Bit_SET);   \
		                                                \
			GPIO_WriteBit (GPIOD, GPIO_Pin_3, Bit_SET);   \
			GPIO_WriteBit (GPIOD, GPIO_Pin_4, Bit_RESET);	\
		  GPIO_WriteBit (GPIOD, GPIO_Pin_5, Bit_SET);   \
		                                                \
		  GPIO_WriteBit (GPIOD, GPIO_Pin_6, Bit_SET);	  \
		  GPIO_WriteBit (GPIOD, GPIO_Pin_7, Bit_RESET);

		
#define DISPLAY_4			                               \
			GPIO_WriteBit (GPIOD, GPIO_Pin_0, Bit_SET);    \
			GPIO_WriteBit (GPIOD, GPIO_Pin_1, Bit_RESET);  \
			GPIO_WriteBit (GPIOD, GPIO_Pin_2, Bit_SET);    \
		                                                 \
			GPIO_WriteBit (GPIOD, GPIO_Pin_3, Bit_SET);    \
			GPIO_WriteBit (GPIOD, GPIO_Pin_4, Bit_RESET);	 \
		  GPIO_WriteBit (GPIOD, GPIO_Pin_5, Bit_SET);    \
		                                                 \
		  GPIO_WriteBit (GPIOD, GPIO_Pin_6, Bit_RESET);	 \
		  GPIO_WriteBit (GPIOD, GPIO_Pin_7, Bit_RESET);  

		
#define DISPLAY_5                                   \
			GPIO_WriteBit (GPIOD, GPIO_Pin_0, Bit_SET);   \
			GPIO_WriteBit (GPIOD, GPIO_Pin_1, Bit_SET);   \
			GPIO_WriteBit (GPIOD, GPIO_Pin_2, Bit_RESET); \
		                                                \
			GPIO_WriteBit (GPIOD, GPIO_Pin_3, Bit_SET);   \
			GPIO_WriteBit (GPIOD, GPIO_Pin_4, Bit_RESET);	\
		  GPIO_WriteBit (GPIOD, GPIO_Pin_5, Bit_SET);   \
		                                                \
		  GPIO_WriteBit (GPIOD, GPIO_Pin_6, Bit_SET);	  \
		  GPIO_WriteBit (GPIOD, GPIO_Pin_7, Bit_RESET);
		
		
#define DISPLAY_6                                   \
			GPIO_WriteBit (GPIOD, GPIO_Pin_0, Bit_SET);   \
			GPIO_WriteBit (GPIOD, GPIO_Pin_1, Bit_SET);   \
			GPIO_WriteBit (GPIOD, GPIO_Pin_2, Bit_RESET); \
		                                                \
			GPIO_WriteBit (GPIOD, GPIO_Pin_3, Bit_SET);   \
			GPIO_WriteBit (GPIOD, GPIO_Pin_4, Bit_SET);	  \
		  GPIO_WriteBit (GPIOD, GPIO_Pin_5, Bit_SET);   \
		                                                \
		  GPIO_WriteBit (GPIOD, GPIO_Pin_6, Bit_SET);	  \
		  GPIO_WriteBit (GPIOD, GPIO_Pin_7, Bit_RESET);
		
		
#define DISPLAY_7                                   \
			GPIO_WriteBit (GPIOD, GPIO_Pin_0, Bit_RESET); \
			GPIO_WriteBit (GPIOD, GPIO_Pin_1, Bit_SET);   \
			GPIO_WriteBit (GPIOD, GPIO_Pin_2, Bit_SET);   \
		                                                \
			GPIO_WriteBit (GPIOD, GPIO_Pin_3, Bit_RESET); \
			GPIO_WriteBit (GPIOD, GPIO_Pin_4, Bit_RESET);	\
		  GPIO_WriteBit (GPIOD, GPIO_Pin_5, Bit_SET);   \
		                                                \
		  GPIO_WriteBit (GPIOD, GPIO_Pin_6, Bit_RESET);	\
		  GPIO_WriteBit (GPIOD, GPIO_Pin_7, Bit_RESET);
		
		
#define DISPLAY_8                                   \
			GPIO_WriteBit (GPIOD, GPIO_Pin_0, Bit_SET);   \
			GPIO_WriteBit (GPIOD, GPIO_Pin_1, Bit_SET);   \
			GPIO_WriteBit (GPIOD, GPIO_Pin_2, Bit_SET);   \
		                                                \
			GPIO_WriteBit (GPIOD, GPIO_Pin_3, Bit_SET);   \
			GPIO_WriteBit (GPIOD, GPIO_Pin_4, Bit_SET);	  \
		  GPIO_WriteBit (GPIOD, GPIO_Pin_5, Bit_SET);   \
		                                                \
		  GPIO_WriteBit (GPIOD, GPIO_Pin_6, Bit_SET);	  \
		  GPIO_WriteBit (GPIOD, GPIO_Pin_7, Bit_RESET);

		
#define DISPLAY_9                                   \
			GPIO_WriteBit (GPIOD, GPIO_Pin_0, Bit_SET);   \
			GPIO_WriteBit (GPIOD, GPIO_Pin_1, Bit_SET);   \
			GPIO_WriteBit (GPIOD, GPIO_Pin_2, Bit_SET);   \
		                                                \
			GPIO_WriteBit (GPIOD, GPIO_Pin_3, Bit_SET);   \
			GPIO_WriteBit (GPIOD, GPIO_Pin_4, Bit_RESET);	\
		  GPIO_WriteBit (GPIOD, GPIO_Pin_5, Bit_SET);   \
		                                                \
		  GPIO_WriteBit (GPIOD, GPIO_Pin_6, Bit_RESET);	\
		  GPIO_WriteBit (GPIOD, GPIO_Pin_7, Bit_RESET);
			
		
		//CASE 10 DOT
#define DOT                                           \
			GPIO_WriteBit (GPIOD, GPIO_Pin_0, Bit_RESET);   \
			GPIO_WriteBit (GPIOD, GPIO_Pin_1, Bit_RESET);   \
			GPIO_WriteBit (GPIOD, GPIO_Pin_2, Bit_RESET);   \
		                                                  \
			GPIO_WriteBit (GPIOD, GPIO_Pin_3, Bit_RESET);   \
			GPIO_WriteBit (GPIOD, GPIO_Pin_4, Bit_RESET);	  \
		  GPIO_WriteBit (GPIOD, GPIO_Pin_5, Bit_RESET);   \
		                                                  \
		  GPIO_WriteBit (GPIOD, GPIO_Pin_6, Bit_RESET);	  \
		  GPIO_WriteBit (GPIOD, GPIO_Pin_7, Bit_SET);     

*/
