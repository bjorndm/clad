/**
* This is a test for memory allocation in the clad test framework.
*/
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "clad/bool.h"
#include "clad/test.h"
#include "clad/memory.h"
#include "clad/nse.h"
#include "clad/sb.h"

#define CSTR "Hello!!!"

TEST_FUNC(clad_sb_init_cstr) {
  struct clad_sb buf;
  TEST_NOTNULL(clad_sb_init_cstr(&buf, CSTR));
  TEST_STREQ(CSTR, buf.bytes);
  TEST_MEMEQ(CSTR, (strlen(CSTR)+1), buf.bytes);
  TEST_INTEQ(buf.length, strlen(CSTR));
  TEST_ASSERT(buf.space > strlen(CSTR));
  clad_sb_done(&buf);
  TEST_DONE();
}

#define CUT_CSTR "Hello"
TEST_FUNC(clad_sb_init_buf) {
  struct clad_sb buf;
  size_t cut_len = strlen(CSTR) - 3;
  TEST_NOTNULL(clad_sb_init_buf(&buf, CSTR, cut_len));
  TEST_STREQ(CUT_CSTR, buf.bytes);
  TEST_MEMEQ(CUT_CSTR, (cut_len+1), buf.bytes);
  TEST_INTEQ(buf.length, cut_len);
  TEST_ASSERT(buf.space > cut_len);
  clad_sb_done(&buf);
  TEST_DONE();
}

#define EMPTY_CSTR ""
TEST_FUNC(clad_sb_init_empty) {
  struct clad_sb buf;
  int cut_len = strlen(CSTR) - 3;
  TEST_NOTNULL(clad_sb_init_empty(&buf));
  TEST_STREQ(EMPTY_CSTR, buf.bytes);
  TEST_MEMEQ(EMPTY_CSTR, 1, buf.bytes);
  TEST_INTEQ(buf.length, 0);
  TEST_INTEQ(buf.space , 0);
  TEST_PTREQ(buf.bytes , (void *) clad_sb_empty_buffer);
  clad_sb_done(&buf);
  TEST_DONE();
}

TEST_FUNC(clad_sb_make_cstr) {
  struct clad_sb * buf;
  TEST_NOTNULL(buf = clad_sb_make_cstr(CSTR));
  TEST_STREQ(CSTR, buf->bytes);
  TEST_MEMEQ(CSTR, (strlen(CSTR)+1), buf->bytes);
  TEST_INTEQ(buf->length , strlen(CSTR));
  TEST_ASSERT(buf->space > strlen(CSTR));
  clad_sb_free(buf);
  TEST_DONE();
}

TEST_FUNC(clad_sb_make_buf) {
  struct clad_sb * buf;
  size_t cut_len = strlen(CSTR) - 3;
  TEST_NOTNULL(buf = clad_sb_make_buf(CSTR, cut_len));
  TEST_STREQ(CUT_CSTR, buf->bytes);
  TEST_MEMEQ(CUT_CSTR, (cut_len+1), buf->bytes);
  TEST_INTEQ(buf->length, cut_len);
  TEST_ASSERT(buf->space > cut_len);
  clad_sb_free(buf);
  TEST_DONE();
}

TEST_FUNC(clad_sb_make_empty) {
  struct clad_sb * buf;
  int cut_len = strlen(CSTR) - 3;
  TEST_NOTNULL(buf = clad_sb_make_empty());
  TEST_STREQ(EMPTY_CSTR , buf->bytes);
  TEST_MEMEQ(EMPTY_CSTR , 1, buf->bytes);
  TEST_INTEQ(buf->length, 0);
  TEST_INTEQ(buf->space , 0);
  TEST_PTREQ(buf->bytes , (void *) clad_sb_empty_buffer);
  clad_sb_free(buf);
  TEST_DONE();
}


int main(void) {
  TEST_INIT();
  TEST_RUN(clad_sb_init_cstr);
  TEST_RUN(clad_sb_init_buf);
  TEST_RUN(clad_sb_init_empty);
  TEST_RUN(clad_sb_make_cstr);
  TEST_RUN(clad_sb_make_buf);
  TEST_RUN(clad_sb_make_empty);
  TEST_REPORT();
}
