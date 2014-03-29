/* Copyright (c) 2004-2012 Sergey Lyubka <valenok@gmail.com>
 All rights reserved

 Enhanced and modified by beoran@gmail.com, 2013.

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/

#ifndef CLAD_SLRE_H_INCLUDED
#define CLAD_SLRE_H_INCLUDED

#include "clad/pp.h"
#include "clad/platform.h"
#include "clad/shared.h"


/* This is a regular expression library that implements a subset of Perl RE.
// Please refer to http://slre.googlecode.com for detailed description.
//
// Supported syntax:
//    ^        Match beginning of a buffer
//    $        Match end of a buffer
//    ()       Grouping and substring capturing
//    [...]    Match any character from set
//    [^...]   Match any character but ones from set
//    \s       Match whitespace
//    \S       Match non-whitespace
//    \d       Match decimal digit
//    \D       Match anything but a decimal digit
//    \a       Match alphabetical character
//    \A       Match anything but an alphabetical character
//    \w       Match alphanumerical character
//    \W       Match anything but an alphanumerical character
//    \b       Match a blank character, i.e. space or tab
//    \B       Match anything but a blank character
//    \x       Match a hexadecimal digit
//    \X       Match anything but a hexadecimal digit
//    \t       Match a tab
//    \r       Match carriage return
//    \n       Match newline
//    +        Match one or more times (greedy)
//    +?       Match one or more times (non-greedy)
//    *        Match zero or more times (greedy)
//    *?       Match zero or more times (non-greedy)
//    ?        Match zero or once
//    \xDD     Match byte with hex value 0xDD
//    \meta    Match one of the meta character: ^$().[*+\?

// Match string buffer "buf" of length "buf_len" against "regexp", which should
// conform the syntax outlined above. "options" could be either 0 or
// CLAD_SLRE_CASE_INSENSITIVE for case-insensitive match. If regular expression
// "regexp" contains brackets, slre_match() will capture the respective
// substring into the passed placeholder. Thus, each opening parenthesis
// should correspond to three arguments passed:
//   placeholder_type, placeholder_size, placeholder_address
//
// Usage example: parsing HTTP request line.
//
//  char method[10], uri[100];
//  int http_version_minor, http_version_major;
//  const char *error;
//  const char *request = " \tGET /index.html HTTP/1.0\r\n\r\n";

//  error = slre_match(0, "^\\s*(GET|POST)\\s+(\\S+)\\s+HTTP/(\\d)\\.(\\d)",
//                     request, strlen(request),
//                     CLAD_SLRE_STRING,  sizeof(method), method,
//                     CLAD_SLRE_STRING, sizeof(uri), uri,
//                     CLAD_SLRE_INT,sizeof(http_version_major),&http_version_major,
//                     CLAD_SLRE_INT,sizeof(http_version_minor),&http_version_minor);
//
//  if (error != NULL) {
//    printf("Error parsing HTTP request: %s\n", error);
//  } else {
//    printf("Requested URI: %s\n", uri);
//  }
//
// If the option CLAD_SLRE_NO_CAPTURE is passed, captures are not stored.
//
// If CLAD_SLRE_CALLBACK is passed as the first variable arument, then the 2 next 
// arguments must be a function pointer of the type * clad_slre_callback, and a void *
// that points to extra data or to NULL. The callback will be called once 
// for every match.
//
// If CLAD_SLRE_CAPTURED is passed, addresses to clad_slre_capture structs 
// must be passed for storage of the results.
// 
// If CLAD_SLRE_IGNORE is passed, then all further captures are ignored.
//
// Return:
//   0: string matched and all captures successfully made
//   non-zero: in this case, the return value is an error value from the enum slre_result.
*/

/* Match options. */
enum clad_slre_option { 
  CLAD_SLRE_CASE_INSENSITIVE = 1, CLAD_SLRE_NO_CAPTURE = 2
};

/* Possible capture types. */
enum clad_slre_capture { 
   CLAD_SLRE_STRING, CLAD_SLRE_INT, CLAD_SLRE_FLOAT, CLAD_SLRE_CALLBACK, CLAD_SLRE_CAPTURED, CLAD_SLRE_IGNORE
};

/* Captured substring */
struct clad_slre_captured {
  const char *ptr;  /* Pointer to the substring. */
  int len;          /* Substring length. */
};


/* Possible results of slre_match. */
enum slre_result {
  CLAD_SLRE_OK                       = 0,
  CLAD_SLRE_ERROR_NO_MATCH           = 1,
  CLAD_SLRE_ERROR_JUMP_OFFSET        = 2,
  CLAD_SLRE_ERROR_CODE_TOO_LONG      = 3,
  CLAD_SLRE_ERROR_DATA_TOO_LONG      = 4,
  CLAD_SLRE_ERROR_NO_PAREN           = 5,
  CLAD_SLRE_ERROR_BAD_PAREN          = 6,
  CLAD_SLRE_ERROR_NO_BRACKET         = 7,
  CLAD_SLRE_ERROR_TOO_MANY_PAREN     = 8,
  CLAD_SLRE_ERROR_INT_FAILED         = 9,
  CLAD_SLRE_ERROR_INT_SIZE           = 10,
  CLAD_SLRE_ERROR_FLOAT_SIZE         = 11,
  CLAD_SLRE_ERROR_FLOAT_FAILED       = 12,
  CLAD_SLRE_ERROR_STRING_SIZE        = 13,
  CLAD_SLRE_ERROR_UNKNOWN_TYPE       = 14,
  CLAD_SLRE_ERROR_TEXT_TOO_LONG      = 15,
  CLAD_SLRE_ERROR_NULL_CAPTURED      = 16,
  CLAD_SLRE_ERROR_LAST               = 225,
};

/* Maximum amount of captures. */
#ifndef CLAD_SLRE_CAPURES_MAX
#define CLAD_SLRE_CAPURES_MAX 64
#endif


/* Callback type to use for CLAD_SLRE_CALLBACK. */
typedef int 
clad_slre_callback(int index, const char * capture, int size, void * data);

/* Matching function. */
CLAD_API int 
clad_slre_match(enum clad_slre_option options, const char *regexp,
                const char *buf, int buf_len, ...);

/* Converts error code to string or NULL if not known. */
CLAD_API const char * 
clad_slre_error(int code);

#endif /* CLAD_SLRE_H_INCLUDED */
