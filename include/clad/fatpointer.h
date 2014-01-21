#ifndef CLAD_FATPOINTER_H_INCLUDED
#define CLAD_FATPOINTER_H_INCLUDED

struct clad_fatpointer {
  size_t size;
  char * ptr;
};

extern CLAD_API struct clad_fatpointer 
clad_fatpointer_make(void * ptr, size_t size);

extern CLAD_API int
clad_fatpointer_ok(struct clad_fatpointer me, size_t index);

extern CLAD_API void *
clad_fatpointer_index(struct clad_fatpointer me, size_t index);

extern CLAD_API void *
clad_fatpointer_get(struct clad_fatpointer me);





#endif

