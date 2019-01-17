/*!
** @file allocation.c
** @version 1.0
** @brief
**         Implementation of allocator functions
*/
/*!
**  @addtogroup allocator_module Memory allocator module documentation
**  @{
*/
#include "allocation.h"


/*!
**     @brief
**         Initialize allocator pool
**     @param
**         unit - pointer to pool
*/
void allocatorInit(AllocatorPool* pool)
{
	if(!pool)
		return;

	pool->start = pool->head = pool->mem;

	AllocatorUnit* curUnit;

	for (curUnit = pool->head; curUnit < (pool->head + BATCH_COUNT); curUnit++)
	{
		curUnit->next = curUnit + 1;
	}
	curUnit->next = NULL;
}


/*!
**     @brief
**         Finds first not used batch and returns pointer to it
**     @param
**         unit - pointer to pool
**     @return
**              - pointer to allocated batch
*/
void* allocBatch(AllocatorPool* pool)
{
	AllocatorUnit* tmp;

	if(!pool)
		return NULL;

	// Out of memory
	if(!pool->head->next)
		return NULL;

	vTaskEnterCritical();
	tmp = pool->head;
	pool->head = pool->head->next;
	vTaskExitCritical();

	return tmp;
}

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
int freeBatch(AllocatorPool* pool, void* batch)
{
	if(!pool)
		return -1;
	if(!batch)
		return -1;

	if ( (batch < (void*)pool) || (batch > (void*)(pool + BATCH_COUNT)) )
		return -1;

	vTaskEnterCritical();
	((AllocatorUnit*)batch)->next = pool->head;
	pool->head = ((AllocatorUnit*)batch);
	vTaskExitCritical();

	return 0;
}


/*!
**     @brief
**         Prints count allocation units and thier
**     @param
**         pool - pointer to pool
**		   place - first unit to print
**		   count - amount of units to print
*/
void printUnits(AllocatorPool* pool, uint32_t place, uint32_t count)
{
	AllocatorUnit* curUnit;

	for (curUnit = pool->start + place; curUnit < (pool->start + count); curUnit++)
	{
		printf("0x%x -> 0x%x\n", curUnit, curUnit->next);
	}
}
/*!
**     @brief
**         Prints pool of empty units in tethered list
**     @param
**         pool - pointer to pool
*/
void printTetheredList(AllocatorPool* pool)
{
	AllocatorUnit* curUnit;
	for (curUnit = pool->head; curUnit != NULL; curUnit = curUnit->next)
	{
		printf("0x%x -> 0x%x\n", curUnit, curUnit->next);
	}
}

/*!
**     @brief
**         Counts elements in list of empty units
**     @param
**         pool - pointer to pool
**     @return
**         		- amount of empty units in pool
*/
uint32_t getUnitsCount(AllocatorPool* pool)
{
	AllocatorUnit* curUnit;
	uint32_t count = 0;

	curUnit = pool->head;

	while(curUnit->next != NULL)
	{
		count++;
		curUnit = curUnit->next;
	}
	return count;
}




/*!
** @}
*/
