  /*******************************************************************
  * @file    MovingAverageFilter.c
  * @author  Tashreef Anowar, Yang Zhou
  * @date    17-February-2014
  * @brief   This file provides functions to Create 
	*          a Moving Average Filter
	********************************************************************/

#include <stdio.h>
#include <MovingAverageFilter.h>

/*
 * Function: MovingAverageFilter
 * ----------------------------
 * Computes the filtered output
 *
 *   @param: InternalStateFilter_t* - pointer to filter structure
 *   @param: uint16_t - unfiltered Vadc
 *
 *   returns: float filtered value
 */
float MovingAverageFilter(InternalStateFilter_t* filterInternalState, float data)
{
	
	float average = 0;
	float movingSum;
	int i;
	
	//puts Vadc in the buffer
	filterInternalState->filterBuffer[filterInternalState->newIndex] = data;
	
	// increments the newIndex, if newIndex points to the last 
	// element of the buffer then newIndex is made 0 to point to
	// beginning of the buffer again
	if(filterInternalState->newIndex ==  FILTER_DEPTH-1)
	{
		filterInternalState->newIndex = 0;
	}
	else
	{
		filterInternalState->newIndex++;
	}
	
	// If filter empty then divide sum by newIndex+1
	if (filterInternalState->fullBuffer_flag < FILTER_DEPTH)
	{
		movingSum = 0;
		i=0;
		while(i <= filterInternalState->fullBuffer_flag)
		{
			movingSum = movingSum + (uint32_t)(filterInternalState->filterBuffer[i]);
			i++;
		}
		
		average = (float)(movingSum / (uint32_t)(filterInternalState->fullBuffer_flag+1));
		filterInternalState->fullBuffer_flag++;
		
	}
	else // if filter full then divide sum by filter size
	{
		movingSum = 0;
		i=0;
		while(i < FILTER_DEPTH)
		{
			movingSum = movingSum + (uint32_t)(filterInternalState->filterBuffer[i]);
			i++;
		}
		average = (float)(movingSum / FILTER_DEPTH);
	}
	
	return average;
	
}

