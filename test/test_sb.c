/**
* This is a test for memory allocation in the clad test framework.
*/
#include <stdlib.h>
#include <stdarg.h>

#include "clad/bool.h"
#include "clad/test.h"
#include "clad/memory.h"
#include "clad/nse.h"
#include "clad/sb.h"

#define CSTR "Hello!!!"

TEST_FUNC(clad_sb_init) {
  struct clad_sb buf;
  TEST_ZERO(clad_sb_init_cstr(&buf, CSTR));
  TEST_STREQ(buf.bytes, CSTR);
  TEST_INTEQ(buf.length, strlen(CSTR));
  TEST_ASSERT(buf.space > strlen(CSTR));
  clad_sb_done(&buf);
  TEST_DONE();
}


int main(void) {
  TEST_INIT();
  TEST_RUN(clad_sb_init);
  TEST_REPORT();
}
