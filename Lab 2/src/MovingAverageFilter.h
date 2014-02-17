#include <stdint.h>
#define FILTER_DEPTH 100

//Filter structure
typedef struct filterState
{
	int newIndex;                            // index to the new position in buffer
	int fullBuffer_flag;                     // indicates full buffer flag 
	uint16_t filterBuffer[FILTER_DEPTH];
} InternalStateFilter_t;
	
float MovingAverageFilter(InternalStateFilter_t*, uint16_t);

