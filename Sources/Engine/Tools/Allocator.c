#include "Engine/Tools/Allocator.h"

#include <stdio.h>

int ptrCounter = 0;

void __drawPtrCount() {
    printf("Pointer count @%d\n", ptrCounter);
}

void* USG_allocate(size_t count, size_t size) {
    void* data = calloc(count, size);
    printf("Allocated pointer   @%p; ", data);
    ptrCounter++;
    __drawPtrCount();
    return data;
}


void USG_deallocate(void * data) {
    printf("Deallocated pointer @%p; ", data);
    ptrCounter--;
    __drawPtrCount();
    free(data);
}