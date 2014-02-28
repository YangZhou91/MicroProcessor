#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "math.h"

void get_calibration_data(int32_t data[3], float* calibrated_data)
{
	
	/* Initlize the matrix Y of calibrated data*/ 
	float A_x1, A_y1, A_z1 = 0;	
	
	/* Initlize the matrix w*/
	float A_x = (float)data[0];
	float A_y = (float)data[1];
	float A_z = (float)data[2];
	float constant_one = 1;	
	//float Matrix_w[4] = {A_x, A_y, A_z, constant_one}; ---> never used
	
	/* Initlize the matrix X with 12 calibration parameter*/
	float ACC_11 = 0.001;
	float	ACC_21 = 0;
	float ACC_31 = 0;
	
	float ACC_12 = 0;
	float ACC_22 = 0.001;
	float ACC_32 = 0.000;
	
	float ACC_13 = 0;
	float ACC_23 = 0;
	float ACC_33 = 0.001;
	
	float ACC_10 = -0.0163;
	float ACC_20 = 0.0719;
	float ACC_30 = 0.0468;
	
	A_x1 = A_x*ACC_11+A_y*ACC_12+A_z*ACC_13 + constant_one*ACC_10;
	A_y1 = A_x*ACC_21+A_y*ACC_22+A_z*ACC_23 + constant_one*ACC_20;
	A_z1 = A_x*ACC_31+A_y*ACC_32+A_z*ACC_33 + constant_one*ACC_30;
	
	/* Clear contents */
	calibrated_data[0] = 0;
	calibrated_data[1] = 0;
	calibrated_data[2] = 0;
	
	/* Fill in with new data */
	calibrated_data[0] = A_x1;
	calibrated_data[1] = A_y1;
	calibrated_data[2] = A_z1;
}
