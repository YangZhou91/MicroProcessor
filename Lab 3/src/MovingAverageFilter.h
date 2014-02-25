  /*******************************************************************
  * @file    MovingAverageFilter.h
  * @author  Tashreef Anowar, Yang Zhou
  * @date    17-February-2014
  * @brief   This file provides functions to Create 
	*          a Moving Average Filter with the filter
	*          structure.
	********************************************************************/
	
#include <stdint.h>

#define FILTER_DEPTH 20

/*
 * struct filterState - Filter structure
 * ----------------------------
 * Filter configuration 
 *
 * int newIndex - index to the new position in buffer
 * int fullBuffer_flag - indicates full buffer flag 
 * uint16_t filterBuffer[FILTER_DEPTH] - array for filter buffer
 */
typedef struct filterState
{
	int newIndex;                            // index to the new position in buffer
	int fullBuffer_flag;                     // indicates full buffer flag 
	uint16_t filterBuffer[FILTER_DEPTH];
} InternalStateFilter_t;


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
float MovingAverageFilter(InternalStateFilter_t*, float);

