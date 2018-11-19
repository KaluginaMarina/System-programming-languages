#ifndef LAB6_MEM_DEBUG_H
#define LAB6_MEM_DEBUG_H

#include <stdio.h>
#include "allocation.h"

#define DEBUG_FIRST_BYTES 4

void memalloc_debug_struct_info( FILE* f, header const* const address );
void memalloc_debug_heap( FILE* f, header const* ptr );
#endif //LAB6_MEM_DEBUG_H
