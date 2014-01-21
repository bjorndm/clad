
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "clad/shared.h"
#include "clad/test.h"

/* Some cute ANSI colors, can be disabled by defining CLAD_TEST_NO_ANSI */
#ifndef CLAD_TEST_NO_ANSI
#define CLAD_TEST_ANSI_R(S) ("\033[1;31m" S "\033[0m")
#define CLAD_TEST_ANSI_G(S) ("\033[1;32m" S "\033[0m")
#define CLAD_TEST_ANSI_Y(S) ("\033[1;33m" S "\033[0m")
#else
#define CLAD_TEST_ANSI_R(S) (S)
#define CLAD_TEST_ANSI_G(S) (S)
#define CLAD_TEST_ANSI_Y(S) (S)
#endif



/* Epsilon for double and float comparisons*/
#ifndef CLAD_TEST_DOUBLE_EPSILON
#define CLAD_TEST_DOUBLE_EPSILON 0.0000000001
#endif 

#ifndef CLAD_TEST_FLOAT_EPSILON
#define CLAD_TEST_FLOAT_EPSILON 0.0000001
#endif 

/** Initializes the test. */
CLAD_API struct clad_test * 
clad_test_init(struct clad_test * test) 
{
  if(!test) return NULL;
  test->failed = test->ok = test->count = 0;
  return test;
}

/** Adds one OK test.*/
CLAD_API struct clad_test * 
clad_test_ok(struct clad_test * test)
{
  test->count ++;
  test->ok    ++;
  return test;
}


/** Fails one test with variable arguments. The failure 
message is written immediately to stderr. */
CLAD_API struct clad_test * 
clad_test_vfail(struct clad_test * test, const char * fmt, va_list ap) 
{
  test->count ++;
  test->failed++;
  fprintf(stderr, CLAD_TEST_ANSI_R("struct clad_test %d failed: "), test->count);
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  return test;
} 


/** Fails one test. */
CLAD_API struct clad_test * 
clad_test_fail(struct clad_test * test, const char * fmt, ...) 
{
  va_list  ap;
  va_start(ap, fmt);
  clad_test_vfail(test, fmt, ap);
  va_end(ap);
  return test;
}


/**
Reports the results of the tests to stderr.
Returns nonzero if there were errors, zero if no errors,
so it can be called in main as return clad_test_report(&test);
*/
CLAD_API int clad_test_report(struct clad_test * test) 
{
  if (test->ok == test->count) {
    fprintf(stderr, CLAD_TEST_ANSI_G("SUCCESS: %d/%d \n"), test->ok, test->count);
    return 0;
  } else {
    fprintf(stderr, CLAD_TEST_ANSI_R("FAILED: %d/%d \n"), test->ok, test->count);
    return 1;
  }
}

/** Tests if an assertion is nonzero with variable arguments. */
CLAD_API struct clad_test *  clad_test_vassert
(struct clad_test * test, int assert, const char * fmt, va_list ap) 
{
  if (assert) {
    clad_test_ok(test);
  } else {
    clad_test_vfail(test, fmt, ap);
  }
  return test;
}


/** Rests if a certain assertion is nonzero, failing a 
test case if it is false. */
CLAD_API struct clad_test *  clad_test_assert
(struct clad_test * test, int assert, const char * fmt, ...)
{
  va_list  ap;  
  va_start(ap, fmt);
  clad_test_vassert(test, assert, fmt, ap);
  va_end(ap); 
  return test;  
}


/** Tests if a pointer is null, Fails the test if it's not so. */
CLAD_API struct clad_test * 
clad_test_null(struct clad_test * test, void * ptr, const char * explain) 
{
  return clad_test_assert(test, ptr == NULL,
              "Pointer should be null: %p; %s",  ptr, explain); 
}

/** Tests if a pointer is not null, Fails the test if it is NULL. */
CLAD_API struct clad_test * 
clad_test_notnull(struct clad_test * test, void * ptr, const char * explain) 
{
  return clad_test_assert(test, ptr != NULL,
  "Pointer should be not null: %p; %s",  ptr, explain);
}



/** Tests if two strings are equal according to strcmp. */
CLAD_API struct clad_test * 
clad_test_streq(struct clad_test * test, char * s1, char * s2, const char * explain) 
{
  return clad_test_assert(test, strcmp(s1, s2) == 0, 
  "Strings should be equal: >%s< >%s<; %s ", s1, s2, explain);
}

/** Tests if two strings are equal according to strncmp. */
CLAD_API struct clad_test * 
clad_test_streqn(struct clad_test * test, char * s1, size_t n, char * s2, 
                          const char * explain) 
{
  return clad_test_assert(test, strncmp(s1, s2, n) == 0, 
  "Strings should be equal: >%s< >%s<; %s ", s1, s2, explain);
}

/** Tests if two memory areas are equal according to memcmp. */
CLAD_API struct clad_test * 
clad_test_memeq(struct clad_test * test, void * m1, size_t n, void * m2,
                  const char * explain) 
{
  if(!m2) return clad_test_fail(test, 
"Memory should be equal but pointer was null: %p %p; %s", m1, m2, explain);
  return clad_test_assert(test, memcmp(m1, m2, n) == 0, 
  "Memory should be equal: %p %p; %s ", m1, m2, explain);
}

/** Tests if two pointers are equal */
CLAD_API struct clad_test * 
 clad_test_ptreq(struct clad_test * test, void *p1, void * p2, const char * explain)
{
  return clad_test_assert(test, p1 == p2, 
  "Pointers should be equal: %p %p; %s ", p1, p2, explain);
}

/** Tests if two pointers are unequal */
CLAD_API struct clad_test * 
clad_test_ptrneq(struct clad_test * test, void *p1, void * p2, 
              const char * explain) {
  return clad_test_assert(test, p1 != p2, 
  "Pointers should not be equal: %p %p; %s ", p1, p2, explain);
}

/** Tests if two integers are equal */
CLAD_API struct clad_test * 
clad_test_inteq(struct clad_test * test, int i1, int i2, const char * explain) 
{
  return clad_test_assert(test, i1 == i2, 
  "Integers should be equal: %d %d; %s ", i1, i2, explain);
}

/** Tests if two integers are not equal */
CLAD_API struct clad_test * 
 clad_test_intneq(struct clad_test * test, int i1, int i2, const char * explain) {
  return clad_test_assert(test, i1 != i2, 
  "Integers should not be equal: %d %d; %s ", i1, i2, explain);
}

/** Tests if two long integers are equal */
CLAD_API struct clad_test * 
 clad_test_longeq(struct clad_test * test, long i1, long i2, const char * explain) {
  return clad_test_assert(test, i1 == i2, 
  "Integers should be equal: %ld %ld; %s ", i1, i2, explain);
}

/** Tests if two long integers are not equal */
CLAD_API struct clad_test * 
 clad_test_longneq(struct clad_test * test, long i1, long i2, const char * explain) {
  return clad_test_assert(test, i1 != i2, 
  "Integers should not be equal: %ld %ld; %s ", i1, i2, explain);
}

/** Tests if two doubles are equal within CLAD_TEST_DOUBLE_EPSILON */
CLAD_API struct clad_test * 
 clad_test_doubleeq(struct clad_test * test, double d1, double d2, const char * explain) {
  double delta = fabs(d2 - d1);
  return clad_test_assert(test, delta < CLAD_TEST_DOUBLE_EPSILON, 
  "Doubles should be equal: %f %f; %s ", d1, d2, explain);
}

/** Tests if two doubles are not more different than CLAD_TEST_DOUBLE_EPSILON */
CLAD_API struct clad_test * 
 clad_test_doubleneq(struct clad_test * test, double d1, double d2, const char * explain) {
  double delta = fabs(d2 - d1);
  return clad_test_assert(test, delta >= CLAD_TEST_DOUBLE_EPSILON, 
  "Doubles should not be equal: %f %f; %s ", d1, d2, explain);
}

/** Tests if two floats are equal within CLAD_TEST_FLOAT_EPSILON */
CLAD_API struct clad_test * 
 clad_test_floateq(struct clad_test * test, float d1, float d2, const char * explain) {
  float delta = d2 - d1;
  delta       = ((delta < 0) ? -delta : delta);
  return clad_test_assert(test, delta < CLAD_TEST_FLOAT_EPSILON, 
  "Floats should be equal: %f %f; %s ", d1, d2, explain);
}

/** Tests if two floats are not more different than CLAD_TEST_FLOAT_EPSILON */
CLAD_API struct clad_test * 
 clad_test_floatneq(struct clad_test * test, float d1, float d2, const char * explain) {
  float delta = d2 - d1;
  delta       = ((delta < 0) ? -delta : delta);
  return clad_test_assert(test, delta >= CLAD_TEST_FLOAT_EPSILON, 
  "Floats should not be equal: %f %f; %s ", d1, d2, explain);
}


/** Tests if an integer has a true value */
CLAD_API struct clad_test * 
 clad_test_true(struct clad_test * test, int boole, const char * explain) {
  return clad_test_assert(test, boole, 
  "Boolean should be TRUE: %d; %s ", boole, explain);
}

/** Tests if an integer has a false value */
CLAD_API struct clad_test * 
 clad_test_false(struct clad_test * test, int boole, const char * explain) {
  return clad_test_assert(test, (!boole), 
  "Boolean should be FALSE: %d; %s ", boole, explain);
}


