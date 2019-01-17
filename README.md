# Memory Allocator for embedded systems
Simple fixed chunk size memory allocator. Based on singly linked list. Freeing and allocating memory operations done by constant time O(1).
# Usage
1) Declare global variable AllocationPool

AllocationPool yourPool;

2) Call initialization function 

allocatorInit(&yourPool);

3) Allocate memory

void* yourPointer = allocBatch(&yourPool);

4) Free memory

freeBatch(&yourPool, yourPointer);

Warning! Never free same chunks of memory more than one time!

