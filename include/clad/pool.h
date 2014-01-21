#ifndef CLAD_POOL_H_INCLUDED
#define CLAD_POOL_H_INCLUDED

struct clad_pool;

/** Allocates a new memory pool that uses the given allocator. 
* Passing null has the same effect as calling clad_pool_make and uses 
* the default allocator.
*/
CLAD_API struct clad_pool * clad_pool_make_with(struct clad_allocator * alloc);


/** Allocates a new memory pool and returns it or NULL if out of memory. */
CLAD_API struct clad_pool * clad_pool_make();

/** Allocates a block of memory in the pool and sets it to zero. 
    Returns NULL if out of memory. */
CLAD_API void * clad_pool_calloc(struct clad_pool * me, size_t size);

/** Deallocates the last pool allocated in the block. Returns 0 if no 
more allocations in the pool are left, 1 if any are left, -1 on error. */
CLAD_API int clad_pool_freelast(struct clad_pool * me);

/** Resizes an area allocated  in the pool. Note that this will involve a 
linear scan of the pool to find the pointer. */
CLAD_API void * clad_pool_realloc(struct clad_pool * me,
                                  void * ptr, size_t newsize);

/** Frees a block in the pool. Note that this will involve a linear scan of 
the pool to find the pointer. */
CLAD_API void * clad_pool_freeone(struct clad_pool * me,
                                  void * ptr, size_t newsize);

/** Frees the pool and all allocated block in it. */
CLAD_API void * clad_pool_free(struct clad_pool * me);


#endif


