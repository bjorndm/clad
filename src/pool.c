
#include <stdlib.h>

#include "clad/shared.h"
#include "clad/memory.h"
#include "clad/allocator.h"
#include "clad/pool.h"
#include "clad/pp.h"
#include "clad/nse.h"

CLAD_NSE_USING(clad_memory, mem);

struct clad_poolblock;

struct clad_poolblock {
  /* Linked stack in reverse order of allocation. */
  struct clad_poolblock * previous;
  /* Allocated pointer. */
  void * ptr;
};


struct clad_pool {
  struct clad_poolblock * poolblock;
};


CLAD_API struct clad_pool * clad_pool_alloc() {
  return mem->calloc(sizeof(struct clad_pool), 1);
}

/** Allocates a new memory pool and returns it or NULL if out of memory. */
CLAD_API struct clad_pool * clad_pool_make() {
  struct clad_pool * me;
  me = clad_pool_alloc();
  if (me) {
    me->poolblock = NULL;
  }
  return me;
}

/** Allocates a block of memory in the pool. Returns NULL if out of memory. */
CLAD_API void * clad_pool_calloc(struct clad_pool * me, size_t size) {
  struct clad_poolblock * newblock;
  if (!me)             return NULL;
  newblock           = clad_calloc(sizeof(struct clad_poolblock), 1);
  if (!newblock)       return NULL;
  newblock->ptr      = clad_calloc(size, 1);
  if (!newblock->ptr) {
    free(newblock);
    return NULL;
  }
  newblock->previous  = me->poolblock;
  me->poolblock       = newblock;
  return me->poolblock->ptr;
}


/** Deallocates the last pool allocated in the block. Returns 0 if no 
more allocations in the pool are left, 1 if any are left, -1 on error. */
CLAD_API int clad_pool_freelast(struct clad_pool * me) {
  struct clad_poolblock * nowblock, * prevblock;
  if (!me)                  return -1;
  nowblock                = me->poolblock;
  if (!nowblock)            return 0;
  prevblock               = nowblock->previous;
  /* Free the pointer and the wrapper block. */
  clad_free(nowblock->ptr);
  clad_free(nowblock);
  /* And oldblock now is the me->poolblock to use */
  me->poolblock           = prevblock;
  if(me->poolblock)         return 1;
  return 0;
}




/** Frees the pool and all allocated block in it. */
CLAD_API void * clad_pool_free(struct clad_pool * me) {
  /* Keep freeing last until nothing to free or error. */
  while(clad_pool_freelast(me) > 0);
  /* Free the pool itself; */
  clad_free(me);
  return NULL;
}








