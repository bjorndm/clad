#include "clad/memory.h"
#include "clad/allocator.h"


CLAD_API struct clad_allocator clad_allocator_get_default() {
  struct clad_allocator result;
  result.allocate = clad_malloc;
  result.free     = clad_free;
  result.resize   = clad_realloc;
  return result;
}



