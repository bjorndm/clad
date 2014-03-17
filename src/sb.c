
#include "clad/platform.h"
#include "clad/memory.h"
#include "clad/sb.h"

#include <string.h>
#include <ctype.h>
#include <stdlib.h>

CLAD_API char clad_sb_empty_buffer[1] = {'\0'};

/** Dynamically allocates a pointer to an empty wrapper structure with no 
 * space available. */
CLAD_API struct clad_sb * 
clad_sb_alloc(void) {
  return clad_calloc(sizeof(struct clad_sb), 1);
}

/** Deallocates the memory the wrapper points to but does not free the 
 * wrapper. Returns me. */
CLAD_API struct clad_sb * 
clad_sb_done(struct clad_sb *me) {
  if ((me->space > 0) && (me->bytes)) {
    clad_free(me->bytes);
    me->bytes = NULL;
  } 
  return me;
}  

/** Calls clad_sb_done if needed and then frees the wrapper. */
CLAD_API struct clad_sb * 
clad_sb_free(struct clad_sb * me) {
  if (me) { clad_sb_done(me); } 
  clad_free(me);
  return NULL;
} 

/** Initializes the string buffer as the empty string. */
CLAD_API struct clad_sb * 
clad_sb_init_empty(struct clad_sb * me) {
  if(!me) return me;
  me->length       = 0;
  me->space = 0;
  me->bytes      = NULL;
  return me;
}

/** Initializes the string buffer from a C string. */
CLAD_API struct clad_sb * 
clad_sb_init_cstr(struct clad_sb * me, char * str) {
  return clad_sb_init_buf(me, str, strlen(str));
}

/** Calculates the space to use for a given string length */
static size_t clad_sb_space_for_len(size_t len)  {
  return (1 + ((len + 1) / CLAD_SB_INCREMENT )) * CLAD_SB_INCREMENT;
}

/* Ensure nul character termination. me->length must have been set correctly. */
static void clad_sb_ensure_nul(struct clad_sb * me) {
    me->bytes[me->length] = '\0'; /* Ensure nul character termination. */
}

/** Initializes the string buffer from a C char buffer with length len. */
CLAD_API struct clad_sb * 
clad_sb_init_buf(struct clad_sb * me, char * str, size_t len) {
  size_t space = clad_sb_space_for_len(len);
  if (!me) return me;
  if (!str) return NULL;
  if (len == 0) { 
    /* special case for empty strings, don't allocate memory yet. */
    return clad_sb_init_empty(me);
  } 
    
  me->bytes = clad_calloc(space, 1);
  
  if (!me->bytes) {
    me->space = CLAD_SB_ERROR_NOMEM;
    return NULL;
  }

  me->space = space;
  me->length       = len;
  memmove(me->bytes, str, len);
  clad_sb_ensure_nul(me);
  
  return me;
}

/** Initializes the string buffer from another clad_sb. */
CLAD_API struct clad_sb * 
clad_sb_init_sb(struct clad_sb * me, const struct clad_sb * other) {
  return clad_sb_init_buf(me, other->bytes, other->length);
}

/** Duplicates a clad_sb. The result must be freed with clad_sb_free(). */
CLAD_API struct clad_sb * 
clad_sb_dup(struct clad_sb * other) {
  return clad_sb_init_sb(clad_sb_alloc(), other);
}

/** Creates an empty string buffer The result must be freed with clad_sb_free(). */
CLAD_API struct clad_sb * 
clad_sb_make_empty() {
  return clad_sb_init_empty(clad_sb_alloc());
}

/** Creates a string buffer from a c string. 
 * The result must be freed with clad_sb_free(). */
CLAD_API struct clad_sb * 
clad_sb_make_cstr(char * cstr) {
  return clad_sb_init_cstr(clad_sb_alloc(), cstr);
}

/** Creates a string buffer from a c byte buffer. 
 * The result must be freed with clad_sb_free(). */
CLAD_API struct clad_sb * 
clad_sb_make_buf(char * cstr, size_t size) {
  return clad_sb_init_buf(clad_sb_alloc(), cstr, size);
}


/** Returns the length of the string buffer in bytes. */
CLAD_API int 
clad_sb_bytesize(struct clad_sb * me) {
  return me->length;
}

/** Returns the pointer to the byte buffer that the clad_sb wraps, 
 or NULL on error or empty string. */
CLAD_API char * 
clad_sb_bytes(struct clad_sb * me) {
  return me->bytes;
}

/** Reallocates the string buffer's bytes to fit a total length of len,
  but only if it's a growth. Does not copy any data. */
CLAD_API int clad_sb_grow(struct clad_sb * me, int len) {
  if (len < 1)               return CLAD_SB_ERROR_BADARG;
  if (len <  me->length)       return CLAD_SB_OK;
  if (len <  me->space) return CLAD_SB_OK;
  int space       = clad_sb_space_for_len(len);
  char * bytes    = clad_realloc(me->bytes, space);
  if (!bytes)       return CLAD_SB_ERROR_NOMEM; 
  me->bytes       = bytes;
  me->length        = len;
  me->space  = space;
  return CLAD_SB_OK;
} 


/** In general clad_sb has functions that work in an immutable fashion, 
 * that is they return a newly allocated result but leave the buffer 
 * itself unchanged, and mutable functions that modify the string itself.  
 * Immutable functions generally return a pointer, mutable an integer. 
 * The integer should be zero on success for mutable ones in most cases, 
 * while immutable functions should return non-NULL on success. 
 */

/** Concatenates a c buffer to the clad_sb */
CLAD_API int 
clad_sb_cat_buf(struct clad_sb * me, char * str, int len) {
  int res;
  /* reallocate needed if the concatenated string does not fit. */
  res = clad_sb_grow(me, me->length + len);
  if (res < 0) return res;
 
  /* copy data */
  memmove(me->bytes + me->length, str, len); 
  /* Set correct size. */
  me->length     = me->length + len; 
  clad_sb_ensure_nul(me);
  return CLAD_SB_OK;
}

/** Concatenates a c string to the clad_sb */
CLAD_API int 
clad_sb_cat_cstr(struct clad_sb * me, char * str) { 
  return clad_sb_cat_buf(me, str, strlen(str));
}

/** Concatenates the contents of a clad_sb other to the clad_sb me */
CLAD_API int 
clad_sb_cat(struct clad_sb * me, const struct clad_sb * other) {
  return clad_sb_cat_buf(me, other->bytes, other->length);
}

/** Appends the character c to the clad_sb me */
CLAD_API int 
clad_sb_append(struct clad_sb * me, char c) {
  int res;
  /* reallocate needed if the concatenated string does not fit. */
  res = clad_sb_grow(me, me->length + 1);
  if (res < 0) return res;
 
  /* copy data */
  me->bytes[me->length] = c; 
    /* Set correct size. */
  me->length++;
  clad_sb_ensure_nul(me);
  return CLAD_SB_OK;
}

typedef int clad_sb_walker(struct clad_sb * me, int index, char c, void * extra);
typedef int clad_sb_simple_mapper(int c);

/** Iterates over the characters of a string. */
CLAD_API int clad_sb_walk(struct clad_sb * me, clad_sb_walker each, void * extra) {
  int index;
  for (index = 0; index < me->length; index++) {
    int res; 
    res = each(me, index, me->bytes[index], extra);
    if (res != CLAD_SB_OK) return res;
  }
  return CLAD_SB_OK;
} 


/** Applies a map of the characters of a string in a simpler fashion. */
CLAD_API int clad_sb_mapchar(struct clad_sb * me, clad_sb_simple_mapper mapper) {
  int index;
  for (index = 0; index < me->length; index++) {
    int res; 
    res = mapper(me->bytes[index]);
    me->bytes[index] = res;
  }
  return CLAD_SB_OK;
} 

static int clad_sb_capitalizer(struct clad_sb * me, int index, char c, void * extra) {
  char newchar = c;
  if ((index == 0) || isspace(me->bytes[index-1])) {
    me->bytes[index] = toupper(c);
  } else {
    me->bytes[index] = tolower(c);
  }
  return CLAD_SB_OK;
}


/** Changes string contents from normal case to Capitalized Case. 
 Only works for ascii characters. */
CLAD_API int 
clad_sb_capitalize(struct clad_sb * me) {
  return clad_sb_walk(me, clad_sb_capitalizer, NULL);
}

/** Changes string contents from normal case to UPPER CASE. 
 Only works for ascii characters. */
CLAD_API int 
clad_sb_uppercase(struct clad_sb * me) {
  return clad_sb_mapchar(me, toupper);
}

/** Changes string contents from normal case to lower case. 
 Only works for ascii characters. */
CLAD_API int 
clad_sb_lowercase(struct clad_sb * me) {
  return clad_sb_mapchar(me, tolower);
}

/** Compares strings as per strncmp. */
CLAD_API int 
clad_sb_cmp(const struct clad_sb * me, const struct clad_sb * other) {
  int len = ((me->length < other->length) ? me->length : other->length);
  return strncmp(me->bytes, other->bytes, len);
}

/** Converts the string to a long integer in the given base, starting at byte index index. 
 * Returns negative on failure. Stores result in result if this is not NULL.*/
CLAD_API int 
clad_sb_index_long(struct clad_sb * me, int index, long int * result, int base) {
  char * endptr;
  long aid = strtol(me->bytes + index, &endptr, base);
  if (result) (*result) = aid;
  if (*endptr != '\0') return CLAD_SB_ERROR_BADARG;
  return CLAD_SB_OK;
}

/** Converts the string to a double, starting at byte index index. 
 * Returns negative on failure. Stores result in result if this is not NULL.*/
CLAD_API int 
clad_sb_index_double(struct clad_sb * me, int index, double * result) {
  char * endptr;
  double aid = strtod(me->bytes + index, &endptr);
  if (result) (*result) = aid;
  if (*endptr != '\0') return CLAD_SB_ERROR_BADARG;
  return CLAD_SB_OK;
}


/** Converts the string to an integer. Returns nonzero on failure. 
 * Stores result in result if this is not NULL. USes strtod with a 0 base, so 
 a number startining with 0x is interpreted as hexadecimal, and one with 0 is 
 interpreted as octal. */
CLAD_API int 
clad_sb_to_long(struct clad_sb * me, long * result) {
  return clad_sb_index_long(me, 0, result, 0);
}

/** Converts the string to a double. Returns nonzero on failure. 
 * Stores result in result if this is not NULL.*/
CLAD_API int 
clad_sb_to_double(struct clad_sb * me, double * result) {
  return clad_sb_index_double(me, 0, result);
}

/** Returns a new cstr that has been padded left and right with the characters 
 * from padding up to a length of length. */
CLAD_API struct clad_sb * 
clad_sb_center_cstr(struct clad_sb * me, int length, const char * padding) {
  /* XXX: todo */
  return NULL;
}


/** Returns the byte from the clad_sb me at byte index index as an 
 unsigned characters. Returns negative on error. */
CLAD_API int clad_sb_at(struct clad_sb * me, int index) {
  if (index < 0) return CLAD_SB_ERROR_BADARG;
  if (index > me->length) return CLAD_SB_ERROR_BADARG;
  return me->bytes[index];
}

/** Returns the last byte of the string buffer before the closing \0 character */
CLAD_API int clad_sb_lastbyte(struct clad_sb * me) {
  return clad_sb_at(me, me->length-1);
}


/** Returns the first byte of the string buffer before the closing \0 character */
CLAD_API int clad_sb_firstbyte(struct clad_sb * me) {
  return clad_sb_at(me, 0);
}


/** Removes the last character from the string and returns it's value
 * as a positive integer (unsigned char) . 
 Returns negative on error. */
CLAD_API int 
clad_sb_chop(struct clad_sb * me) {
  int result;
  if (me->length < 1) return CLAD_SB_ERROR_BADARG;
  result = (unsigned char) me->bytes[me->length-1];
  me->length--;
  me->bytes[me->length] = '\0';
  return result;
}

/** Removes the last character from the string if it is a newline. 
 * Also works on carriage-return newline and carriage return only.
 */
CLAD_API int 
clad_sb_chomp(struct clad_sb * me) {
  char last = clad_sb_lastbyte(me);
  if (last  == '\n') {
    clad_sb_chop(me);
    char prev = clad_sb_lastbyte(me);
    if (prev == '\r') {
      clad_sb_chop(me);
    }
  } else if (last == '\r') {
    clad_sb_chop(me);
  }
  return CLAD_SB_OK;
}

/** Sanity checks me and index, particularily , 
 if me and me->bytes are net, and if index is not out of
    bounds for me. Returns 0 if OK, negative if not.*/
CLAD_API int 
clad_sb_index_error(const struct clad_sb * me, int begin) {
  if (!me)              return CLAD_SB_ERROR_BADARG;
  if (!me->bytes)       return CLAD_SB_ERROR_BADARG;
  if (begin < 0)        return CLAD_SB_ERROR_BADARG;
  if (begin > me->length) return CLAD_SB_ERROR_BADARG;
  return CLAD_SB_OK;  
}

/** Clamp length so it is within range for the string buffer me */
CLAD_API int 
clad_sb_clamp_length(const struct clad_sb * me, int start, int * length) {
  if ((*length + start) > me->length) {
    (*length) = me->length - start;
  }
  return CLAD_SB_OK;
}


/** Fetches a substring from me into result. Result must point to a 
 buffer big enough to hold len characters. */
CLAD_API int 
clad_sb_substr_buf(struct clad_sb * me, int begin, int len, char * result) {
  if (clad_sb_index_error(me, begin)) return CLAD_SB_ERROR_BADARG;
  /* truncate length */
  clad_sb_clamp_length(me, begin, &len);
  memmove(result, me->bytes + begin, len);
  return CLAD_SB_OK;
}

/** Fetches a substring from me into result. */
CLAD_API int 
clad_sb_get_substr(struct clad_sb * me, int begin, int len, struct clad_sb * result) {
  int aid;
  aid = clad_sb_grow(result, len);
  if (aid < 0) return aid;
  clad_sb_substr_buf(me, begin, len, result->bytes);
  if (aid < 0) return aid;
  clad_sb_ensure_nul(me);
  return aid;
}

/** Returns length bytes of the clad_sb, starting at start. */
CLAD_API struct clad_sb * 
clad_sb_mid(const struct clad_sb * me, int begin, int size) {
  if (clad_sb_index_error(me, begin)) return NULL;  
  /* truncate length */
  clad_sb_clamp_length(me, begin, &size);
  return clad_sb_make_buf(me->bytes + begin, size);
}

/** Returns the first length bytes of the clad_sb. */
CLAD_API struct clad_sb * 
clad_sb_left(const struct clad_sb * me, int size) {
  return clad_sb_mid(me, 0, size);
}

/** Returns the last length bytes of the clad_sb. */
CLAD_API struct clad_sb * 
clad_sb_right(const struct clad_sb * me, int length) {
  return clad_sb_mid(me, me->length - length, length);
}

/** "Deletes" length bytes from clad_sb, starting at start. 
 In realty, the bytes are moved around. */
CLAD_API int 
clad_sb_delete(struct clad_sb * me, int start, int size) {
  return clad_sb_get_substr(me, start, size, me);
}

/** Inserts other into the clad_sb, at start byte index. */
CLAD_API int
clad_sb_insert(struct clad_sb * me, int start, const struct clad_sb * other) {
  return CLAD_SB_ERROR_BADARG;
}

/** Inserts rsize bytes from other into the clad_sb, at start byte index. */
CLAD_API int
clad_sb_insert_size
(struct clad_sb * me, int start, const struct clad_sb * other, int rsize);

/** Inserts cstr into the clad_sb, at start byte index. */
CLAD_API int
clad_sb_insert_cstr(struct clad_sb * me, int start, const char * cstr);

/** Inserts buffer into the clad_sb, at start byte index. */
CLAD_API int
clad_sb_insert_buf(struct clad_sb * me, int start, const char * cstr, int size);

/** Replaces length bytes, starting at start, and inserts 
 * rsize bytes from the clad_sb in stead. */
CLAD_API int 
clad_sb_replace_size
(struct clad_sb * me, int start, int length, const struct clad_sb * other, int rsize);

/** Replaces length bytes, starting at start, and inserts 
 * the clad_sb in stead. */
CLAD_API int 
clad_sb_replace
(struct clad_sb * me, int start, int length, const struct clad_sb * other);

/** Replaces length bytes, starting at start, and inserts 
 * rsize bytes from the buffer in stead. */
CLAD_API int 
clad_sb_replace_buf
(struct clad_sb * me, int start, int length, const char * other, int rsize);

/** Replaces length bytes, starting at start, and inserts 
 * the string other in stead. */
CLAD_API int 
clad_sb_replace_cstr
(struct clad_sb * me, int start, int length, const char * other);


/** Replaces all characters in from with those in to. 
 Only works for ascii. */
CLAD_API int clad_sb_tr_cstr(struct clad_sb * me, const char * from, const char * to);

/** Finds the first occurrence of the byte b, starting at start(inclusive), and 
 * returns it's index. 
 * Return negative if not found or on parameter errors. */
CLAD_API int 
clad_sb_chr(const struct clad_sb * me, int start, char byte);

/** Finds the last  occurrence of the byte b, starting at start (inclusive), and 
 * returns it's index. 
 * Return negative if not found or on parameter errors. */
CLAD_API int 
clad_sb_rchr(const struct clad_sb * me, int start, char byte);

/** Finds the first occurence of other in me, starting from start. Returns 
 the index, or negative if not found or on error. */
CLAD_API int 
clad_sb_find(const struct clad_sb * me, int start, const struct clad_sb * other);

/** Finds the first occurence of other in me, starting from start. Returns 
 the index, or negative if not found or on error. Only the first size 
 characters are checked. */
CLAD_API int 
clad_sb_find_size(const struct clad_sb * me, int start, const struct clad_sb * other, int size);

/** Finds the first occurence of other in me, starting from start. Returns 
 the index, or negative if not found or on error. */
CLAD_API int 
clad_sb_find_cstr(const struct clad_sb * me, int start, const char * other);

/** Finds the first occurence of other in me, starting from start. Returns 
 the index, or negative if not found or on error. */
CLAD_API int 
clad_sb_find_buf(const struct clad_sb * me, int start, const char * other, int size);

/** Finds all occurrences of "from", and replaces them by size characters 
 * from "to". Returns the amount of replacements made, 0 if nothing replaced, and 
 * negative on error.
 */
CLAD_API int 
clad_sb_substitute_size
(struct clad_sb * me, int start, const struct clad_sb * from, const struct clad_sb * to, int size);

/** Finds all occurrences of "from", and replaces them by characters 
 * from "to". Returns the amount of replacements made, 0 if nothing replaced, and 
 * negative on error.
 */
CLAD_API int 
clad_sb_substitute
(struct clad_sb * me, int start, const struct clad_sb * from, const struct clad_sb * to);

/** Finds all occurrences of "from", and replaces them by size characters 
 * from "to". Returns the amount of replacements made, 0 if nothing replaced, and 
 * negative on error.
 */
CLAD_API int 
clad_sb_substitute_buf
(struct clad_sb * me, int start, const char * from, int fromsize, 
 const char * to, int tosize, int size);

/** Finds all occurrences of "from", and replaces them by size characters 
 * from "to". Returns the amount of replacements made, 0 if nothing replaced, and 
 * negative on error.
 */
CLAD_API int 
clad_sb_substitute_cstr
(struct clad_sb * me, int start, const char * from, const char * to, int size);