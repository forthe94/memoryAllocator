/*
 * allocation.c
 *
 *  Created on: Jan 10, 2019
 *      Author: tetenkov
 */
#include "allocation.h"

//Batch[BATCH_COUNT] allocatorunit;




// Initialize allocator unit and returns pointer to first data batch
void* allocatorInit(AllocatorUnit* unit)
{
	uint16_t i;
	uint16_t j;

	if( ( BATCH_COUNT > sizeof(uint16_t) ) || ( BATCH_SIZE > sizeof(uint16_t) ) )
	{
		printf("Inadmissible allocator parametrs");
		return NULL;
	}
	void* savedBatch = &unit->data[0];

	unit->end = unit + BATCH_COUNT;
	for(i = 0; i < BATCH_COUNT; i++, unit++)
	{
		unit->used = 0;
		for (j = 0; j < BATCH_SIZE; j++)
		{
			unit->data[j] = 0;
		}
	}

	return savedBatch;
}

//Finds first not used batch and returns pointer to it
void* allocBatch(AllocatorUnit* unit)
{
	AllocatorUnit* unitStart = unit;

	if (unit->used = 0)
	{
		//first unit not used
		unit->used = 1;
		return &unit->data[0];
	}
	else
	{
		if (unit->end > unitStart + BATCH_COUNT)
			return NULL;
		else
			return (unit->end + 1);
	}
}
