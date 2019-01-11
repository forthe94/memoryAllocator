/*
 * allocation.h
 *
 *  Created on: Jan 10, 2019
 *      Author: tetenkov
 */

#ifndef ALLOCATION_H_
#define ALLOCATION_H_

#include "u_types.h"


#define BATCH_SIZE 4
#define BATCH_COUNT 32



typedef struct AllocatorUnit
{
	struct AllocatorUnit* start;	//Pointer to the start of blocks chain
	struct AllocatorUnit* end;		//Pointer to the end of blocks chain
	uint8_t data[BATCH_SIZE];
	uint8_t used;	//Data in usage flag
}AllocatorUnit;


typedef struct AllocatorPool
{
	AllocatorUnit* head;
} AllocatorPool;

void* allocatorInit(AllocatorUnit* unit);
void* allocBatch(AllocatorUnit* unit);
int freeBatch(AllocatorUnit* unit, void* batch);
AllocatorUnit* batchToUnit(void* batch);
void printUnits(AllocatorUnit* unit, uint16_t place, uint16_t count);

#endif /* ALLOCATION_H_ */
