/**
* This is a test for tsting the clad test famework.
*/
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#include "clad/bool.h"
#include "clad/test.h"
#include "clad/slre.h"


TEST_FUNC(clad_slre_1) {
  const char * banana = "bananas";
  struct clad_slre_captured captures[16];
  memset(captures, 0, sizeof(struct clad_slre_captured)); 
  int result = 
  clad_slre_match(0, "nana", banana, strlen(banana), CLAD_SLRE_CAPTURED, captures + 0);
  TEST_INTEQ(result, 0);
  printf("Callback: %d %s\n", captures[0].len, captures[0].ptr);
  TEST_INTEQ(captures[0].len, 4);
  TEST_INTEQ(captures[0].ptr - banana, 2);
  return 0;  
}

static int test_callback_1(int index, const char * capture, 
                         int size, void * data) {
  TEST_SET_POINTER(data);
  TEST_STREQ(capture, "nana");
  printf("Callback: %d %s\n", size, capture);
  TEST_INTEQ(size, 4);
  return 0;
}

TEST_FUNC(clad_slre_2) {
  const char * banana = "bananas";
  int result = 
  clad_slre_match(0, "nana", banana, strlen(banana), CLAD_SLRE_CALLBACK, test_callback_1, TEST_POINTER());
  TEST_INTEQ(result, 0);
  return 0;  
}



int main(void) {
  TEST_INIT();
  TEST_RUN(clad_slre_1);
  TEST_RUN(clad_slre_2);
  TEST_REPORT();
}



