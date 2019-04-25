#ifndef __USAGI_ALLOCATOR_H__
#define __USAGI_ALLOCATOR_H__

#include <stdlib.h>

void* USG_allocate(size_t count, size_t size);
void USG_deallocate(void* data);

#endif /* __USAGI_ALLOCATOR_H__ */