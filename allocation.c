/*
 * allocation.c
 *
 *  Created on: Jan 10, 2019
 *      Author: tetenkov
 */
#include "allocation.h"

//Batch[BATCH_COUNT] allocatorunit;




// Initialize allocator unit and returns pointer to first data batch
// params:
// unit - pointer to first unit of pool
void* allocatorInit(AllocatorUnit* unit)
{
	uint16_t i;
	uint16_t j;

	if( ( BATCH_COUNT > 0xffff ) || ( BATCH_SIZE > 0xffff ) )
	{
		printf("Inadmissible allocator parametrs\n");
		return NULL;
	}
	void* savedBatch = &unit->data[0];

	unit->end = unit + BATCH_COUNT;		//make pointer to chain end
	printf("allocator main chain end 0x%x\n", unit->end);

	for(i = 0; i < BATCH_COUNT; i++, unit++)
	{
		unit->used = 0;
		for (j = 0; j < BATCH_SIZE; j++)
		{
			unit->data[j] = 0;
		}
	}

	unit->start = unit - BATCH_COUNT;	//make pointer to chain start
	printf("allocator main chain start 0x%x\n", unit->start);

	return savedBatch;
}

//Finds first not used batch and returns pointer to it
// params:
// unit - pointer to first unit of pool
void* allocBatch(AllocatorUnit* unit)
{
	AllocatorUnit* unitStart = unit;
	while (unit < unitStart + BATCH_COUNT)
	{
		if (unit->used == 0)			//first unit not used
		{
			unit->used = 1;

			if ( (unit+1)->used == 0 )		//next unit not used
			{
				//move pointer to end of chain for next unit
				(unit+1)->end = unit->end;
				//move pointer to start of chain for last unit
				unit->end->start = (unit+1);

				//make new chain
				unit->start = unit;
				unit->end = unit;
			}

			if ( (unit+1)->used == 1)			//next unit used
			{
				//need to add new block to chain of used units

				//new pointer to the end of chain for new used unit
				unit->end = (unit+1)->end;

				//dont need pointer to start for this unit anymore
				unit->start = NULL;

				//dont need pointer to end for next unit anymore
				(unit+1)->end = NULL;

				//new pointer for the start of chain for last unit
				(unit+1)->end->start = unit;
			}



			return (void*)&unit->data[0];
		}
		else
		{
			unit = unit->end + 1;
		}
	}
	return NULL;
}


//Frees batch
// params:
// unit - pointer to first unit of pool
// batch - batch to free
uint8_t freeBatch(AllocatorUnit* unit, void* batch)
{

}

//Prints count allocation units from place
// params:
// unit - pointer to first unit of pool
// place - first unit to print
// count - amount of units to print
void printUnits(AllocatorUnit* unit, uint16_t place, uint16_t count)
{
	uint16_t i;
	printf("%d allocator units from %d: ", count, place);
	for (i = place; i < count; i++)
	{
		printf("%d ",(unit+i)->used);
	}
	printf("\n");
}
