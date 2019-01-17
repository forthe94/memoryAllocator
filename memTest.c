/*!
** @file memTest.c
** @version 1.0
** @brief
**         Testing allocator functions
*/
/*!
**  @addtogroup allocator_module Memory allocator module documentation
**  @{
*/
#include "allocation.h"
#include "u_types.h"
#include <system.h>
//#include "clib.h"

#define randomize()	    syscall(SYS_randomize, 0, 0, 0);


/*!
 * 		@brief
 * 			Allocates all memory, then randomly returns some chunks
 * 			back, after returns all left chunks and check if list
 * 			length is proper.
 * 		@param
 * 			- pointer to pool
 * 		@return
 * 			- 0 on succes
 * 			- -1 on failure
 */

int testAlocFreeAllMem(AllocatorPool* pool)
{
	randomize();

	printf("\nAllocating all free %d units from pool\n", getUnitsCount(pool));
    void* newBatch[2*BATCH_COUNT];

    uint32_t j = 0;
    uint32_t i = 0;

    for(i = 0;;i++)
    {
    	newBatch[i] = allocBatch(pool);
    	if (!newBatch[i])
    		break;
    }
    uint32_t count = getUnitsCount(pool);
    if (!count)
    	printf("Allocated %d units, %d units left in pool\n", i, count);
    else
    {
    	printf("Failed to allocate all unit from pool,%d units left in pool\n",
    			count);
    	return -1;
    }
    for (j = 0; j < i; j++)
    {
    	uint32_t number = rand() % i;

    	if (!newBatch[number])
    		continue;

    	freeBatch(pool, newBatch[number]);
    	newBatch[number] = NULL;
    }
    printf("Freed some batches from pool, units left %d\n", getUnitsCount(pool));

    for (j = 0;j<=i;j++)
    {
    	if (!newBatch[j])
    		continue;

    	freeBatch(pool, newBatch[j]);
    	newBatch[j] = NULL;
    }
    uint32_t afterTestCount = getUnitsCount(pool);
    if(i == afterTestCount)
    {
    	printf("Freed all left batches, Test passed, %d free units in pool\n",
    			afterTestCount);
    	return 0;
    }
    else
    {
    	printf("Test failed, %d used units wasn't freed\n\n", count - afterTestCount);
    	return -1;
    }

}

/*!
** @}
*/
