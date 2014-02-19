#include "stm32f4_discovery_lis302dl.h"

#include <stdio.h>

typedef struct
{
	uint8_t axes_x;
	uint8_t axes_y;
	uint8_t axes_z;
}axes_data;

void set_Accelerometer_MEM(void);
axes_data read_Accelerometer_MEM(void);