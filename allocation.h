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
	uint8_t used;	//Data in usage flag
	uint8_t data[BATCH_SIZE];
}AllocatorUnit;


typedef struct AllocatorPool
{
	AllocatorUnit* head;
} AllocatorPool;

void* allocatorInit(AllocatorUnit*);
void* allocBatch(AllocatorUnit*);
void printUnits(AllocatorUnit*, uint16_t, uint16_t);

#endif /* ALLOCATION_H_ */
