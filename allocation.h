/*
 * allocation.h
 *
 *  Created on: Jan 10, 2019
 *      Author: tetenkov
 */

#ifndef ALLOCATION_H_
#define ALLOCATION_H_

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#define BATCH_SIZE 4
#define BATCH_COUNT 32



typedef struct AllocatorUnit
{
    struct AllocatorUnit* next;
    uint8_t data[BATCH_SIZE - sizeof(char*)];
}AllocatorUnit;


typedef struct AllocatorPool
{
    AllocatorUnit* start;
	AllocatorUnit* head;
    AllocatorUnit mem[BATCH_COUNT];
} AllocatorPool;

void allocatorInit(AllocatorPool* pool);
void* allocBatch(AllocatorUnit* unit);
int freeBatch(AllocatorUnit* unit, void* batch);
AllocatorUnit* batchToUnit(void* batch);
void printUnits(AllocatorUnit* unit, uint16_t place, uint16_t count);

#endif /* ALLOCATION_H_ */
