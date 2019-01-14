/*
 * allocation.c
 *
 *  Created on: Jan 10, 2019
 *      Author: tetenkov
 */
#include "allocation.h"


// Initialize allocator pool
// params:
// unit - pointer to pool
void allocatorInit(AllocatorPool* pool)
{
	if(!pool)
		return;

	pool->start = pool->head = pool->mem;

	AllocatorUnit* curUnit;

	for (curUnit = pool->head; curUnit < (pool->head + BATCH_COUNT - 1); curUnit++)
	{
		curUnit->next = curUnit + 1;
	}
	curUnit->next = NULL;
}

// Finds first not used batch and returns pointer to it
// params:
// unit - pointer to first unit of pool
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


// Frees batch
// params:
// unit - pointer to first unit of pool
// batch - batch to free
// return 0 on sucsess
int freeBatch(AllocatorPool* pool, void* batch)
{
	if(!pool)
		return -1;
	if(!batch)
		return -1;

	if ( (batch < (void*)pool) || (batch > (void*)(pool + BATCH_COUNT - 1)) )
		return -1;

	vTaskEnterCritical();
	((AllocatorUnit*)batch)->next = pool->head;
	pool->head = ((AllocatorUnit*)batch);
	vTaskExitCritical();

	return 0;
}



// Prints count allocation units and thier
// pointers from place
// params:
// pool - pointer to pool
// place - first unit to print
// count - amount of units to print
void printUnits(AllocatorPool* pool, uint32_t place, uint32_t count)
{
	AllocatorUnit* curUnit;

	for (curUnit = pool->start + place; curUnit < (pool->start + count); curUnit++)
	{
		printf("0x%x -> 0x%x\n", curUnit, curUnit->next);
	}
}

// Prints pool of empty units in tethered list
void printTetheredList(AllocatorPool* pool)
{
	AllocatorUnit* curUnit;
	for (curUnit = pool->head; curUnit != NULL; curUnit = curUnit->next)
	{
		printf("0x%x -> 0x%x\n", curUnit, curUnit->next);
	}
}
