#ifndef CLAD_ALLOCATOR_H_INCLUDED
#define CLAD_ALLOCATOR_H_INCLUDED

/* 
An allocator is a struct that describes an interface 
that allows the allocation and deallocation of memory resources.
*/

typedef void * clad_allocator_do_allocate(size_t size);
typedef void   clad_allocator_do_free(void * ptr);
typedef void * clad_allocator_do_resize(void * ptr, size_t size);

struct clad_allocator {
  clad_allocator_do_allocate    * allocate;
  clad_allocator_do_free        * free;
  clad_allocator_do_resize      * resize;
};


/* Returns a struct filed in with the default allocator 
(which uses clad_malloc, clad_realloc and clad_free. */
struct clad_allocator clad_allocator_get_default();










#endif /* CLAD_ALLOCATOR_H_INCLUDED */
