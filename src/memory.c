
#include <stdlib.h>

#include "clad/shared.h"
#include "clad/memory.h"


CLAD_API void * clad_calloc(size_t size, size_t amount) {
  return calloc(size, amount);
}

CLAD_API void * clad_malloc(size_t size) {
  return malloc(size);
}


CLAD_API void * clad_realloc(void * old, size_t size) {
  return realloc(old, size);
}

CLAD_API void clad_free(void * old) {
  free(old);
}

/** Struct for namespace emulation. */
CLAD_API const struct clad_memory_api clad_memory_implementation = {
  clad_calloc,
  clad_malloc,
  clad_realloc,
  clad_free
};


