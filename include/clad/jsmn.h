/*

Copyright (c) 2010 Serge A. Zaitsev

Modified for use in CLAD in 2014 by Bjorn De Meyer.

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

#ifndef CLAD_JSMN_H_INCLUDED
#define CLAD_JSMN_H_INCLUDED

/**
 * JSON type identifier. Basic types are:
 * o Object
 * o Array
 * o String
 * o Other primitive: number, boolean (true/false) or null
 */
enum clad_jsmn_type {
  CLAD_JSMN_PRIMITIVE   = 0,
  CLAD_JSMN_OBJECT      = 1,
  CLAD_JSMN_ARRAY       = 2,
  CLAD_JSMN_STRING      = 3
} ;

enum clad_jsmn_error {
  /* Not enough tokens were provided */
  CLAD_JSMN_ERROR_NOMEM = -1,
  /* Invalid character inside JSON string */
  CLAD_JSMN_ERROR_INVAL = -2,
  /* The string is not a full JSON packet, more bytes expected */
  CLAD_JSMN_ERROR_PART  = -3,
  /* Everything was fine */
  CLAD_JSMN_SUCCESS     = 0
};

/**
 * JSON token description.
 * @param    type   type (object, array, string etc.)
 * @param    start  start position in JSON data string
 * @param    end    end position in JSON data string
 * @param    size   size of the object JSON data string
 * @param    parent index to the parent object.
 */
struct clad_jsmn_token {
  enum clad_jsmn_type type;
  int start;
  int end;
  int size;
  int parent;
} 

/**
 * JSON parser. Contains an array of token blocks available. Also stores
 * the string being parsed now and current position in that string
 */
struct clad_jsmn_parser {
  unsigned int pos; /* offset in the JSON string */
  int toknext; /* next token to allocate */
  int toksuper; /* superior token node, e.g parent object or array */
  int strict; /* Is the parser in strict mode or not. */
};

/**
 * Create JSON parser over an array of tokens. Stict is struct is true,
 * otherwise uses permissive parsing.
 */
void clad_jsmn_init(struct clad_jsmn_parser *parser, int strict);

/**
 * Run JSON parser. It parses a JSON data string into and array of tokens,
 * each describing a single JSON object.
 */
enum clad_jsmn_errror
  clad_jsmn_parse(struct clad_jsmn_parser *parser, const char *js,
                  struct clad_jsmn_token *tokens, unsigned int num_tokens);

#endif /* CLAD_JSMN_H_INCLUDED */
