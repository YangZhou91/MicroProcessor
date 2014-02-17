#include <stdio.h>
#include <MovingAverageFilter.h>

float MovingAverageFilter(InternalStateFilter_t* filterInternalState, uint16_t VADC)
{
	
	float average = 0;
	uint32_t movingSum;
	int i;
	
	filterInternalState->filterBuffer[filterInternalState->newIndex] = VADC;
	
	if(filterInternalState->newIndex ==  FILTER_DEPTH-1)
	{
		filterInternalState->newIndex = 0;
	}
	else
	{
		filterInternalState->newIndex++;
	}
	
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
	else
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

