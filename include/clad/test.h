#ifndef CLAD_TEST_H_INCLUDED
#define CLAD_TEST_H_INCLUDED

#include "clad/shared.h"
#include "clad/pp.h"


/* Simple unit testing.*/
struct clad_test {
  int count;  /* total amount of tests */
  int ok;     /* total amount of ok tests */
  int failed; /* total amount of failed tests */
  int should_fail; /* amount of tests that actually should fail */
};


/** Initializes the test. */
CLAD_API struct clad_test *  clad_test_init(struct clad_test * test);

/** Sets the amount of tests that should fail.*/
CLAD_API struct clad_test *  
clad_test_should_fail(struct clad_test * test, int should_fail);


/** Adds one OK test.*/
CLAD_API struct clad_test *  clad_test_ok(struct clad_test * test);

/** Fails one test with variable arguments. The failure 
message is written immediately to stderr. */
CLAD_API struct clad_test * 
clad_test_vfail(struct clad_test * test, const char * fmt, va_list ap);


/** Fails one test. */
CLAD_API struct clad_test * 
clad_test_fail(struct clad_test * test, const char * fmt, ...);


/**
Reports the results of the tests to stderr.
Returns nonzero if there were errors, zero if no errors,
so it can be called in main as return clad_test_report(&test);
*/
CLAD_API int clad_test_report(struct clad_test * test);

/** Tests if an assertion is nonzero with variable arguments. */
CLAD_API struct clad_test *  clad_test_vassert
(struct clad_test * test, int assert, const char * fmt, va_list ap);

/** Rests if a certain assertion is nonzero, failing a 
test case if it is false. */
CLAD_API struct clad_test *  clad_test_assert
(struct clad_test * test, int assert, const char * fmt, ...);

/** Tests if a pointer is null, Fails the test if it's not so. */
CLAD_API struct clad_test * 
clad_test_null(struct clad_test * test, void * ptr, const char * explain);

/** Tests if a pointer is not null, Fails the test if it is NULL. */
CLAD_API struct clad_test * 
clad_test_notnull(struct clad_test * test, void * ptr, const char * explain);

/** Tests if two strings are equal according to strcmp. */
CLAD_API struct clad_test * 
clad_test_streq(struct clad_test * test, char * s1, char * s2, 
                const char * explain);

/** Tests if two strings are equal according to strncmp. */
CLAD_API struct clad_test * 
clad_test_streqn(struct clad_test * test, char * s1, size_t n, char * s2,
                 const char * explain);

/** Tests if two memory areas are equal according to memcmp. */
CLAD_API struct clad_test * 
clad_test_memeq(struct clad_test * test, void * m1, size_t n, void * m2,
                const char * explain);

/** Tests if two pointers are equal */
CLAD_API struct clad_test * 
clad_test_ptreq(struct clad_test * test, void *p1, void * p2, 
                const char * explain);

/** Tests if two pointers are unequal */
CLAD_API struct clad_test * 
clad_test_ptrneq(struct clad_test * test, void *p1, void * p2, 
                 const char * explain);

/** Tests if two integers are equal */
CLAD_API struct clad_test * 
clad_test_inteq(struct clad_test * test, int i1, int i2, const char * explain);

/** Tests if two integers are not equal */
CLAD_API struct clad_test * 
clad_test_intneq(struct clad_test * test, int i1, int i2, const char * explain);

/** Tests if two long integers are equal */
CLAD_API struct clad_test * 
clad_test_longeq(struct clad_test * test, long i1, long i2, 
                 const char * explain);

/** Tests if two long integers are not equal */
CLAD_API struct clad_test * 
clad_test_longneq(struct clad_test * test, long i1, long i2, 
                   const char * explain);

/** Tests if two doubles are equal within CLAD_TEST_DOUBLE_EPSILON */
CLAD_API struct clad_test * 
clad_test_doubleeq(struct clad_test * test, double d1, double d2, 
                   const char * explain);

/** Tests if two doubles are not more different than CLAD_TEST_DOUBLE_EPSILON */
CLAD_API struct clad_test * 
clad_test_doubleneq(struct clad_test * test, double d1, double d2, 
                    const char * explain);

CLAD_API struct clad_test * 
clad_test_floateq(struct clad_test * test, float d1, float d2, 
                  const char * explain);

/** Tests if two floats are not more different than CLAD_TEST_FLOAT_EPSILON */
CLAD_API struct clad_test * 
clad_test_floatneq(struct clad_test * test, float d1, float d2, 
                   const char * explain);

/** Tests if an integer has a true value */
CLAD_API struct clad_test * 
clad_test_true(struct clad_test * test, int boole, const char * explain);

/** Tests if an integer has a false value */
CLAD_API struct clad_test * 
clad_test_false(struct clad_test * test, int boole, const char * explain);


/* Macros to help with calling tested and test report functions.
* Important notice: these macros assume that a struct clad_test * t_ exists
* in scope.
*/

#define TEST_FILELINE_STR() " " CLAD_PP_FILE_STR() " line nr:" CLAD_PP_LINE_STR()
#define TEST_LINE(CALL) CLAD_PP_JOINSTR(CLAD_PP_TOSTR(CALL),TEST_FILELINE_STR())

#define TEST_CAID(CALL, TEXT)         CALL, TEXT
#define TEST_CALL(CALL)               TEST_CAID(CALL, TEST_LINE(CALL))

#define TEST_TRUE(CALL)               clad_test_true(t_,   (int)TEST_CALL(CALL))
#define TEST_FALSE(CALL)              clad_test_false(t_,  (int)TEST_CALL(CALL))
#define TEST_ASSERT(CALL)             clad_test_assert(t_,      TEST_CALL(CALL))
#define TEST_NULL(CALL)               clad_test_null(t_,        TEST_CALL(CALL))
#define TEST_NOTNULL(CALL)            clad_test_notnull(t_,     TEST_CALL(CALL))

#define TEST_STREQ(STR, CALL)         \
  clad_test_streq(t_,  (char *)STR, (char *)TEST_CALL(CALL))

#define TEST_STREQN(STR, SIZE, CALL)  \
  clad_test_streqn(t_, (char *)STR, SIZE, (char *)TEST_CALL(CALL))

#define TEST_MEMEQ(MEM, SIZE, CALL)   \
  clad_test_memeq(t_,  MEM, SIZE,TEST_CALL(CALL))
  
#define TEST_PTREQ(PTR, CALL)         \
  clad_test_ptreq(t_,  PTR, TEST_CALL(CALL))
  
#define TEST_PTRNEQ(PTR, CALL)        \
  clad_test_ptrneq(t_,  PTR, TEST_CALL(CALL))
  
#define TEST_INTEQ(INT, CALL)         \
  clad_test_inteq(t_,  INT, TEST_CALL(CALL))
  
#define TEST_INTNEQ(INT, CALL)        \
  clad_test_intneq(t_, INT, TEST_CALL(CALL))
  
#define TEST_LONGEQ(INT, CALL)        \
  clad_test_longeq(t_,  INT, TEST_CALL(CALL))

#define TEST_LONGNEQ(INT, CALL)       \
  clad_test_longneq(t_, INT, TEST_CALL(CALL))
  
#define TEST_DOUBLEEQ(INT, CALL)      \
  clad_test_doubleeq(t_,  INT, TEST_CALL(CALL))
  
#define TEST_DOUBLENEQ(INT, CALL)     \
  clad_test_doubleneq(t_, INT, TEST_CALL(CALL))
  
#define TEST_FLOATEQ(INT, CALL)       \
  clad_test_floateq(t_,  INT, TEST_CALL(CALL))
  
#define TEST_FLOATNEQ(INT, CALL)      \
  clad_test_floatneq(t_, INT, TEST_CALL(CALL))

#define TEST_ZERO(CALL)               TEST_INTEQ(0, CALL)

/* Other utility macros. They are syntactic, so you may dislike them.
* But they are very handy for unit testing C. 
*/
#define TEST_FUNC(NAME)       \
  struct clad_test * test_##NAME(struct clad_test * t_) 
#define TEST_DONE()           return t_ ;
#define TEST_RUN(NAME)        test_##NAME(t_)
#define TEST_INIT()           \
  struct clad_test ts_ , * t_; t_ = &ts_ ; clad_test_init(t_)
#define TEST_REPORT()         return clad_test_report(t_);

/* Pointer to the active test struct */
#define TEST_POINTER() t_

/* Set up a pointer to the active test struct from an incoming pointer. 
 Useful in test callbacks. */
#define TEST_SET_POINTER(DATA) \
  struct clad_test * t_ = DATA ;


/* Set up a pointer to the active test struct from an incoming pointer. 
 Useful in test callbacks. */




#endif
