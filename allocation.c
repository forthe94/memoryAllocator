/*
 * allocation.c
 *
 *  Created on: Jan 10, 2019
 *      Author: tetenkov
 */
#include "allocation.h"

//Batch[BATCH_COUNT] allocatorunit;

uint8_t offset = 2*sizeof(AllocatorUnit*);


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

// Finds first not used batch and returns pointer to it
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
			if (unit->end == NULL)
			{
				return NULL;
			}
			unit = unit->end + 1;
		}
	}
	return NULL;
}


// Frees batch
// params:
// unit - pointer to first unit of pool
// batch - batch to free
// return 0 on sucsess
int freeBatch(AllocatorUnit* firstUnit, void* batch)
{
	if ((batch < (void*)firstUnit) || (batch > (void*)(firstUnit + BATCH_COUNT)))
	{
		return -1;
	}

	AllocatorUnit* unit = (AllocatorUnit*)((char*)batch - offset);

	if (((char*)unit - (char*)firstUnit) % sizeof(AllocatorUnit))
	{
		printf("Bad alignment\n");
		return -1;
	}
	// Cant free not used unit
	if (unit->used == 0)
	{
		return -1;
	}

	if (unit == firstUnit)		//processing unit on the left side
	{
		if ((unit + 1)->used)
		{
			//move pointer to end of next unit
			(unit + 1)->end = unit->end;
			//move poitner of start of chain to next unit
			unit->end->start = unit + 1;
			//make new chain
			unit->start = unit;
			unit->end = unit;
		}
		else
		{
			//move pointer to start of end of next chain to unit
			(unit + 1)->end->start = unit;
			//move poitner to end of unit to end of chain
			unit->end = (unit + 1)->end;
			//remove not used pointes
			unit->start = (unit + 1)->end = NULL;
		}
		unit->used = 0;
		return 0;

	}
	if (unit == firstUnit + BATCH_COUNT)		//processing unit on the rigth side
	{
		if ((unit - 1)->used)
		{
			//move pointer to start of prev unit
			(unit - 1)->start = unit->start;
			//move poitner of end of chain to prev unit
			unit->start->end = unit - 1;
			//make new chain
			unit->start = unit;
			unit->end = unit;
		}
		else
		{
			//move pointer to end of start of prev chain to unit
			(unit - 1)->start->end = unit;
			//move poitner to end of unit to end of chain
			unit->start = (unit - 1)->start;
			//remove not used pointes
			unit->end = (unit - 1)->start = NULL;
		}
		unit->used = 0;
		return 0;
	}
	if ( (unit - 1)->used  &&  (unit + 1)->used && unit>firstUnit && unit<(firstUnit + BATCH_COUNT))	//Freeing unit surrounded by used units
	{
		//find start of chain
		AllocatorUnit* chainStart = unit - 1;
		while(!chainStart--);
		if(!chainStart)
		{
			printf("failed to find chainStart\n");
			return -1;
		}
		printf("chainStart = 0x%x\n", chainStart);

		//move pointer to end of next unit
		(unit + 1)->end = unit->end;
		//move pointer to start of end of next chain
		chainStart->end->start = unit + 1;

				//move pointer to start of prev unit
		(unit - 1)->start = unit->start;
		//move pointer to end of start of prev chain
		chainStart->end = unit - 1;

		//make new chain
		unit->start = unit;
		unit->end = unit;
		unit->used = 0;
		return 0;
	}
	return -1;
}



// Prints count allocation units from place
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
