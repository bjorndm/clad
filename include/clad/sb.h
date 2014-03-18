#ifndef CLAD_STRAND_H_INCLUDED
#define CLAD_STRAND_H_INCLUDED

#include "clad/pp.h"
#include "clad/platform.h"
#include "clad/shared.h"

enum clad_sb_constants {
  CLAD_SB_OK               =  0  ,
  CLAD_SB_STATIC           = -1  ,
  CLAD_SB_ERROR_NOMEM      = -128,
  CLAD_SB_ERROR_BADARG     = -256,
  /* Clad  string buffer space is allocated with these increments. */
  CLAD_SB_INCREMENT        =  64 ,
};


/* An empty character buffer to initialize empty stringbuffers with. */
CLAD_API const char clad_sb_empty_buffer[1];


/* An sb is a dynamically allocated string buffer. */
struct clad_sb {
  /* Pointer to bytes of data. */
  char * bytes;
  /* Allocated space. Must be at least length+1, or 0 for the empty string buffer. */
  size_t space;
  /* Actual string length in bytes (not characters). */
  size_t length;
};


/** Dynamically allocates a pointer to an empty wrapper structure with no space available. */
CLAD_API struct clad_sb * 
clad_sb_alloc(void);

/** Deallocates the memory the wrapper points to but does not free the 
 * wrapper. Returns me. */
CLAD_API struct clad_sb * 
clad_sb_done(struct clad_sb *me);  

/** Calls clad_sb_done if needed and then frees the wrapper. */
CLAD_API struct clad_sb * 
clad_sb_free(struct clad_sb * me); 

/** Initializes the string buffer as the empty string. */
CLAD_API struct clad_sb * 
clad_sb_init_empty(struct clad_sb * me);

/** Initializes the string buffer from a C string. */
CLAD_API struct clad_sb * 
clad_sb_init_cstr(struct clad_sb * me, char * str);

/** Initializes the string buffer from a C char buffer with length len. */
CLAD_API struct clad_sb * 
clad_sb_init_buf(struct clad_sb * me, char * str, size_t len);

/** Initializes the string buffer from another clad_sb. */
CLAD_API struct clad_sb * 
clad_sb_init_sb(struct clad_sb * me, const struct clad_sb * other);

/** Duplicates a clad_sb. The result must be freed with clad_sb_free(). */
CLAD_API struct clad_sb * 
clad_sb_dup(struct clad_sb * other);

/** Creates an empty string buffer The result must be freed with clad_sb_free(). */
CLAD_API struct clad_sb * 
clad_sb_make_empty();

/** Creates a string buffer from a c string. 
 * The result must be freed with clad_sb_free(). */
CLAD_API struct clad_sb * 
clad_sb_make_cstr(char * cstr);

/** Creates a string buffer from a c byte buffer. 
 * The result must be freed with clad_sb_free(). */
CLAD_API struct clad_sb * 
clad_sb_make_buf(char * cstr, size_t size);

/** Detaches the buffer from the clad_sb. The buffer must be freed with 
 the currently active default deallocator. */
CLAD_API int 
clad_sb_detach(struct clad_sb * me, size_t * size, char ** buffer);

/** Returns the length of the string buffer in bytes. */
CLAD_API int 
clad_sb_bytesize(struct clad_sb * me);

/** Returns the pointer to the bute bbuffer that the clad_sb wraps, 
 or NULL on error or empty string. */
CLAD_API char * 
clad_sb_bytes(struct clad_sb * me);

/** In general clad_sb has functions that work in an immutable fashion, 
 * that is they return a newly allocated result but leave the buffer 
 * itself unchanged, and mutable functions that modify the string itself.  
 * Immutable functions generally return a pointer, mutable an integer. 
 * The integer should be zero on succcess for mutable ones in most cases, 
 * while immutable functions should return non-NULL on success. 
 */

/** Concatenates a c buffer to the clad_sb */
CLAD_API int 
clad_sb_cat_buf(struct clad_sb * me, char * str, int len);

/** Concatenates a c string to the clad_sb */
CLAD_API int 
clad_sb_cat_cstr(struct clad_sb * me, char * str);

/** Concatenates the contents of a clad_sb other to the clad_sb me */
CLAD_API int 
clad_sb_cat(struct clad_sb * me, const struct clad_sb * other);

/** Appends the character c to the clad_sb me */
CLAD_API int 
clad_sb_append(struct clad_sb * me, char c);

/** Changes string contents from normal case to Capitalized Case. 
 Only works for ascii characters. */
CLAD_API int 
clad_sb_capitalize(struct clad_sb * me);

/** Changes string contents from normal case to UPPER CASE. 
 Only works for ascii characters. */
CLAD_API int 
clad_sb_uppercase(struct clad_sb * me);

/** Changes string contents from normal case to lower case. 
 Only works for ascii characters. */
CLAD_API int 
clad_sb_lowercase(struct clad_sb * me);

/** Compares strings as per strncmp. */
CLAD_API int 
clad_sb_cmp(const struct clad_sb * me, const struct clad_sb * other);

/** Reallocates the string buffer's bytes to fit a total length of len,
  but only if it's a growth. Does not copy any data. */
CLAD_API int clad_sb_grow(struct clad_sb * me, size_t len);

/** Converts the string to an integer. Returns nonzero on failure. 
 * Stores result in result if this is not NULL. USes strtod with a 0 base, so 
 a number startining with 0x is interpreted as hexadecimal, and one with 0 is 
 interpreted as octal. */
CLAD_API int 
clad_sb_to_long(struct clad_sb * me, long * result);

/** Converts the string to a double. Returns nonzero on failure. 
 * Stores result in result if this is not NULL.*/
CLAD_API int 
clad_sb_to_double(struct clad_sb * me, double * result);

/** Converts the string to a long integer in the given base, starting at byte index index. 
 * Returns negative on failure. Stores result in result if this is not NULL.*/
CLAD_API int 
clad_sb_index_long(struct clad_sb * me, int index, long int * result, int base);

/** Converts the string to a double, starting at byte index index. 
 * Returns negative on failure. Stores result in result if this is not NULL.*/
CLAD_API int 
clad_sb_index_double(struct clad_sb * me, int index, double * result);

/** Returns a new cstr that has been padded left and right with the characters from padding up to a length of length. */
CLAD_API struct clad_sb * 
clad_sb_center_cstr(struct clad_sb * me, int length, const char * padding);

/** Removes the last character from the string if it is a newline. */
CLAD_API int 
clad_sb_chomp(struct clad_sb * me);

/** Removes the last character from the string and returns it's value. */
CLAD_API int 
clad_sb_chop(struct clad_sb * me);

/** Fetches a substring from me into result. */
CLAD_API int 
clad_sb_get_substr(struct clad_sb * me, int begin, int len, struct clad_sb * result);

/** Returns length bytes of the clad_sb, starting at start. */
CLAD_API struct clad_sb * 
clad_sb_mid(const struct clad_sb * me, int start, int size);

/** Returns the first length bytes of the clad_sb. */
CLAD_API struct clad_sb * 
clad_sb_left(const struct clad_sb * me, int size);

/** Returns the last length bytes of the clad_sb. */
CLAD_API struct clad_sb * 
clad_sb_right(const struct clad_sb * me, int size);

/** Deletes length bytes from clad_sb, starting at start */
CLAD_API int 
clad_sb_delete(struct clad_sb * me, int start, int size);

/** Inserts other into the clad_sb, at start byte index. */
CLAD_API int
clad_sb_insert(struct clad_sb * me, int start, const struct clad_sb * other);

/** Inserts rsize bytes from other into the clad_sb, at start byte index. */
CLAD_API int
clad_sb_insert_size
(struct clad_sb * me, int start, const struct clad_sb * other, int rsize);

/** Inserts cstr into the clad_sb, at start byte index. */
CLAD_API int
clad_sb_insert_cstr(struct clad_sb * me, int start, const char * cstr);

/** Inserts cstr into the clad_sb, at start byte index. */
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
CLAD_API int
clad_sb_tr_cstr(struct clad_sb * me, const char * from, const char * to);

/** Finds the first occurrence of the byte b, starting at start(inclusive), and 
 * returns it's index. 
 * Return negative if not found or on parameter errors. */
CLAD_API int 
clad_sb_chr(const struct clad_sb * me, int start, char byte);

/** Finds the last  occurrence of the byte b, starting at start (inclusive), and 
 * returns it's index. 
 * Return negative if not found or on parameter errors. */
CLAD_API int 
clad_sb_chr(const struct clad_sb * me, int start, char byte);

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
(struct clad_sb * me, int start, 
 const struct clad_sb * from, const struct clad_sb * to, int size);

/** Finds all occurrences of "from", and replaces them by characters 
 * from "to". Returns the amount of replacements made, 0 if nothing replaced, and 
 * negative on error.
 */
CLAD_API int 
clad_sb_substitute
(struct clad_sb * me, int start, const struct clad_sb * from, 
 const struct clad_sb * to);

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




/** 
 * Ruby api inspiration. 
 *  :%, :*, :+, :<<, :[], :[]=, :between?, :bytes, :bytesize, :byteslice, :capitalize, :capitalize!, :casecmp, :center, :chars, :chomp, :chomp!, :chop, :chop!, :chr, :clear, :codepoints, :concat, :count, :crypt, :delete, :delete!, :downcase, :downcase!, :dump, :each_byte, :each_char, :each_codepoint, :each_line, :empty?, :encode, :encode!, :encoding, :end_with?, :force_encoding, :getbyte, :gsub, :gsub!, :hex, :index, :insert, :intern, :length, :lines, :ljust, :lstrip, :lstrip!, :match, :next, :next!, :oct, :ord, :partition, :prepend, :replace, :reverse, :reverse!, :rindex, :rjust, :rpartition, :rstrip, :rstrip!, :scan, :setbyte, :size, :slice, :slice!, :split, :squeeze, :squeeze!, :start_with?, :strip, :strip!, :sub, :sub!, :succ, :succ!, :sum, :swapcase, :swapcase!, :to_c, :to_f, :to_i, :to_r, :to_str, :to_sym, :tr, :tr!, :tr_s, :tr_s!, :unpack, :upcase, :upcase!, :upto, :valid_encoding?
 *
 */



#endif /* CLAD_MEMORY_H_INCLUDED */

