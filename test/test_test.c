/**
* This is a test for tsting the clad test famework.
*/
#include <stdlib.h>
#include <stdarg.h>

#include "clad/bool.h"
#include "clad/test.h"


static int assert_true() {
  return CLAD_TRUE;
}


TEST_FUNC(clad_test) {
  int  * paid;
  int  * paid2;
  int    iaid, iaid2;
  long   l1  , l2;
  double d1  , d2;
  float  f1  , f2;
  
  char * s1 = "hi";
  char * s2 = "hi";
  char * s3 = "hello";
  
  iaid = CLAD_TRUE;
  TEST_TRUE(iaid);
  iaid = CLAD_FALSE;
  TEST_FALSE(iaid);
  TEST_ASSERT(assert_true());
  paid = NULL;
  TEST_NULL(paid);
  paid = & iaid;
  TEST_NOTNULL(paid);
  TEST_STREQ(s1, s2);
  TEST_STREQN(s1, 1, s2);
  TEST_MEMEQ(s1, 2, s2);
  paid  = & iaid;
  paid2 = & iaid;
  TEST_PTREQ(paid, paid2);
  TEST_PTRNEQ(s1, s3);
  iaid  = 1;
  iaid2 = 1;
  TEST_INTEQ(iaid, iaid2);
  iaid  = 1;
  iaid2 = 2;
  TEST_INTNEQ(iaid, iaid2);
  l1    = -1;
  l2    = -1;
  TEST_LONGEQ(l1, l2);
  l1    = -1;
  l2    = -1234;
  TEST_LONGNEQ(l1, l2);
  d1    = 1.234;
  d2    = 1.234;
  TEST_DOUBLEEQ(d1, d2);
  d1    = 1.234;
  d2    = 4.321;
  TEST_DOUBLENEQ(d1, d2);
  f1    = 1.234f;
  f2    = 1.234f;
  TEST_FLOATEQ(f1, f2);
  f1    = 1.234f;
  f2    = 4.321f;
  TEST_FLOATNEQ(f1, f2);
  iaid  = 0;
  TEST_ZERO(iaid);
  TEST_DONE();
}


int main(void) {
  TEST_INIT();
  TEST_RUN(clad_test);
  TEST_REPORT();
}



