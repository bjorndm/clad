/**
* This is a test for memory allocation in the clad test framework.
*/
#include <stdlib.h>
#include <stdarg.h>

#include "clad/bool.h"
#include "clad/test.h"
#include "clad/memory.h"
#include "clad/nse.h"

USING(clad_memory, cm);



TEST_FUNC(clad_malloc_ns) {
  void * ptr1, * ptr2;
  
  ptr1 = NULL;
  ptr2 = NULL;
  ptr1 = cm->malloc(123);
  ptr2 = cm->malloc(123);
  TEST_PTRNEQ(ptr1, ptr2);
  cm->free(ptr2);
  cm->free(ptr1);
  TEST_DONE();
}

TEST_FUNC(clad_malloc) {
  void * ptr1, * ptr2;
  ptr1 = NULL;
  ptr2 = NULL;
  ptr1 = clad_malloc(123);
  ptr2 = clad_malloc(123);
  TEST_PTRNEQ(ptr1, ptr2);
  clad_free(ptr2);
  clad_free(ptr1);
  TEST_DONE();
}

TEST_FUNC(clad_calloc) {
  int * ptr1, * ptr2;
  ptr1 = NULL;
  ptr2 = NULL;
  ptr1 = clad_calloc(123, sizeof(int));
  ptr2 = clad_calloc(123, sizeof(int));
  TEST_PTRNEQ(ptr1, ptr2);
  TEST_ZERO(ptr1[7]);
  TEST_ZERO(ptr2[7]);
  clad_free(ptr2);
  clad_free(ptr1);
  TEST_DONE();
}

TEST_FUNC(clad_realloc) {
  int * ptr1, * ptr2, * paid;
  ptr1 = NULL;
  ptr2 = NULL;
  ptr1 = clad_calloc(123, sizeof(int));
  ptr2 = clad_calloc(123, sizeof(int));
  TEST_PTRNEQ(ptr1, ptr2);
  TEST_ZERO(ptr1[7]);
  TEST_ZERO(ptr2[7]);
  paid = clad_realloc(ptr1, sizeof(int) * 200);
  paid[150] = 77;
  TEST_INTEQ(77, paid[150]);
  clad_free(paid);
  clad_free(ptr2);
  TEST_DONE();
}

int main(void) {
  TEST_INIT();
  TEST_RUN(clad_malloc);
  TEST_RUN(clad_calloc);
  TEST_RUN(clad_realloc);
  TEST_RUN(clad_malloc_ns);
  TEST_REPORT();
}
