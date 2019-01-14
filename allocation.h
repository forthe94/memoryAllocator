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
#define BATCH_COUNT 4



typedef struct AllocatorUnit
{
	struct AllocatorUnit* next;	//Pointer to the start of blocks chain
	uint8_t data[BATCH_SIZE - sizeof(char*)];
}AllocatorUnit;


typedef struct AllocatorPool
{
	AllocatorUnit* start;
	AllocatorUnit* head;
	AllocatorUnit mem[BATCH_COUNT];
} AllocatorPool;

void allocatorInit(AllocatorPool* pool);
void* allocBatch(AllocatorPool* pool);
int freeBatch(AllocatorPool* pool, void* batch);
void printUnits(AllocatorPool* pool, uint32_t place, uint32_t count);
void printTetheredList(AllocatorPool* pool);

#endif /* ALLOCATION_H_ */
