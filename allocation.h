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
	uint8_t used;	//Data in usage flag
	struct AllocatorUnit* end;		//Pointer to end of blocks chain
	uint8_t data[BATCH_SIZE];
}AllocatorUnit;

void* allocatorInit(AllocatorUnit*);
void* allocBatch(AllocatorUnit*);

#endif /* ALLOCATION_H_ */
