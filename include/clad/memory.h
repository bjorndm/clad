#ifndef CLAD_MEMORY_H_INCLUDED
#define CLAD_MEMORY_H_INCLUDED

#include "clad/pp.h"
#include "clad/platform.h"
#include "clad/shared.h"

/* Wrappers around stdlib, this is unfortunately needed for some platforms 
where memory allocated by a dll may not be compatible with memory 
allocated by the program itself. */

CLAD_API void * clad_calloc(size_t size, size_t amount);
CLAD_API void * clad_malloc(size_t size);
CLAD_API void * clad_realloc(void * old, size_t size);
CLAD_API void   clad_free(void * old);


/* Helpers for name space emulation. */
typedef void * clad_calloc_api(size_t size, size_t amount);
typedef void * clad_malloc_api(size_t size);
typedef void * clad_realloc_api(void * old, size_t size);
typedef void   clad_free_api(void * old);

/* Name space members... */
struct clad_memory_api {
  clad_calloc_api  * calloc;
  clad_malloc_api  * malloc;
  clad_realloc_api * realloc;
  clad_free_api    * free;
};

/* Struct for name space emulation. */
extern CLAD_API struct clad_memory_api clad_memory_implementation;


#endif /* CLAD_MEMORY_H_INCLUDED */

