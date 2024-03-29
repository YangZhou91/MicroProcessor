#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <tilt_angle_calculation.h>
#include "math.h"

float calculate_pitch(float* calibrated_data)
{
	float pitch = 0;
	float degrees = 180/PI;
	float A_x1 = calibrated_data[0];
	float A_y1 = calibrated_data[1];
	float A_z1 = calibrated_data[2];
	float A_y1_square = pow(A_y1, 2);
	float A_z1_square = pow(A_z1, 2);
	float denominator = sqrt(A_y1_square+A_z1_square);
	
	pitch = atan(A_x1/denominator) * degrees;
	
	return pitch;
}

float calculate_roll(float* calibrated_data)
{
	float roll = 0;
	float degrees = 180/PI;
	float A_x1 = calibrated_data[0];
	float A_y1 = calibrated_data[1];
	float A_z1 = calibrated_data[2];
	float A_x1_square = pow(A_x1, 2);
	float A_z1_square = pow(A_z1, 2);
	float denominator = sqrt(A_x1_square+A_z1_square);
	
	roll = atan(A_y1/denominator) * degrees;
	
	return roll;
}
