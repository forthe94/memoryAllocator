/*
 * allocation.c
 *
 *  Created on: Jan 10, 2019
 *      Author: tetenkov
 */
#include "allocation.h"

//Batch[BATCH_COUNT] allocatorunit;

uint8_t offset = 2*sizeof(AllocatorUnit*);


// Initialize allocator
// params:
// pool - pointer allocator pool
// unit - pointer to first unit of pool
void allocatorInit(AllocatorPool* pool)
{
    pool->start = pool->mem;
    pool->head = pool->mem;
    AllocatorUnit* curUnit;
    for(curUnit = pool->start; curUnit < pool->start + BATCH_COUNT - 1; curUnit++)
    {
        curUnit->next = curUnit->next + 1;
    }
    curUnit->next = NULL;
}

// Finds first not used batch and returns pointer to it
// params:
// unit - pointer to first unit of pool
void* allocBatch(AllocatorUnit* unit)
{
    return NULL;
}


// Frees batch
// params:
// unit - pointer to first unit of pool
// batch - batch to free
// return 0 on sucsess
int freeBatch(AllocatorUnit* firstUnit, void* batch)
{
    return 0;
}



// Prints count allocation units from place
// params:
// unit - pointer to first unit of pool
// place - first unit to print
// count - amount of units to print
void printUnits(AllocatorUnit* unit, uint16_t place, uint16_t count)
{

}
