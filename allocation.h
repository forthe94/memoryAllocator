/*!
** @file allocation.h
** @version 1.0
** @brief
**         Implementation of allocator functions
*/
/*!
**  @addtogroup allocator_module Memory allocator module documentation
**  @{
*/

#ifndef ALLOCATION_H_
#define ALLOCATION_H_

#include "u_types.h"
#include <system.h>

#define BATCH_SIZE 16
#define BATCH_COUNT 200



typedef struct AllocatorUnit
{
	struct AllocatorUnit* next;	//Pointer to the start of blocks chain
	uint8_t data[BATCH_SIZE - sizeof(char*)];
}AllocatorUnit;


typedef struct AllocatorPool
{
	AllocatorUnit* start;
	AllocatorUnit* head;
	AllocatorUnit mem[BATCH_COUNT+1];
} AllocatorPool;


/*!
**     @brief
**         Initialize allocator pool
**     @param
**         unit - pointer to pool
*/
void allocatorInit(AllocatorPool* pool);

/*!
**     @brief
**         Finds first not used batch and returns pointer to it
**     @param
**         unit - pointer to pool
**     @return
**              - pointer to allocated batch
*/
void* allocBatch(AllocatorPool* pool);

/*!
**     @brief
**         Frees batch
**     @param
**         pool - pointer to pool
**		   batch - batch to free
**     @return
**               - 0 on succes
**               - -1 on fail
*/
int freeBatch(AllocatorPool* pool, void* batch);

/*!
**     @brief
**         Prints count allocation units and thier
**     @param
**         pool - pointer to pool
**		   place - first unit to print
**		   count - amount of units to print
*/
void printUnits(AllocatorPool* pool, uint32_t place, uint32_t count);


/*!
**     @brief
**         Prints pool of empty units in tethered list
**     @param
**         pool - pointer to pool
*/
void printTetheredList(AllocatorPool* pool);


/*!
**     @brief
**         Counts elements in list of empty units
**     @param
**         pool - pointer to pool
**     @return
**         		- amount of empty units in pool
*/
uint32_t getUnitsCount(AllocatorPool* pool);


/*!
 * 		@brief
 * 			Allocates all memory, then randomly returns some chunks
 * 			back, after returns all left chunks and check if list
 * 			length is proper.
 * 		@param
 * 			pointer to pool
 */

int Test1(AllocatorPool* pool);

#endif /* ALLOCATION_H_ */

/*!
** @}
*/
