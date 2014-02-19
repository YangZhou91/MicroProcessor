#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "math.h"
#include "atan_LUT.h"
#include "accelerometer_conf.h"

//NOTE TO STUDENTS: Uncomment the version of drivers related to your sensor
//#include "lis3dsh.h"
//#include "stm32f4_discovery_lis302dl.h"

char kata2[16];
int8_t data_x, data_y, data_z;

int main()
{
		axes_data realtime_data;
		set_Accelerometer_MEM();
	
		while(1)
		{
				realtime_data = read_Accelerometer_MEM();
				data_x = realtime_data.axes_x;
				data_y = realtime_data.axes_y;
				data_z = realtime_data.axes_z;
				printf("x: %d \t", data_x);
				printf("y: %d \t", data_y);
				printf("z: %d \n", data_z);
		}
		
		return 0;
}







