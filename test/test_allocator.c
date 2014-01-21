/**
* This is a test for tsting the clad test famework.
*/
#include <stdlib.h>
#include <stdarg.h>

#include "clad/bool.h"
#include "clad/test.h"
#include "clad/allocator.h"


static int assert_true() {
  return CLAD_TRUE;
}


TEST_FUNC(clad_allocator) {
  int  * paid = NULL;
  struct clad_allocator cl;
  cl   = clad_allocator_get_default();
  paid = cl.allocate(sizeof(int) * 123);
  TEST_NOTNULL(paid);
  paid[120] = 12;
  TEST_INTEQ(12, paid[120]);
  cl.free(paid);
  return 0;
}


int main(void) {
  TEST_INIT();
  TEST_RUN(clad_allocator);
  TEST_REPORT();
}



