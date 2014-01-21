#ifndef CLAD_VARIANT_H_INCLUDED
#define CLAD_VARIANT_H_INCLUDED

#include "clad/shared.h"

enum clad_variant_type {
  CLAD_VARIANT_NONE       ,
  CLAD_VARIANT_SIGNED_CHAR,
  CLAD_VARIANT_UNSIGNED_CHAR,
  CLAD_VARIANT_SIGNED_SHORT,
  CLAD_VARIANT_UNSIGNED_SHORT,
  CLAD_VARIANT_SIGNED_INT,
  CLAD_VARIANT_UNSIGNED_INT,
  CLAD_VARIANT_SIGNED_LONG,
  CLAD_VARIANT_UNSIGNED_LONG,
  CLAD_VARIANT_FLOAT,
  CLAD_VARIANT_DOUBLE
};

union clad_variant { 
  struct {
    enum clad_variant_type type;
  } none;
  
  struct {
    enum clad_variant_type type;
    signed char            value;
  } sc ;
  
  struct {
    enum clad_variant_type type;
    signed int             value;
  } si;
};
  
  
CLAD_API union clad_variant clad_variant_from_int(int value);

CLAD_API int clad_variant_to_int(union clad_variant me, int * value);




/*
struct clad_variant { 
  enum clad_variant_type t;
  union clad_variant_value_private_ {
  signed   char   sc;
  unsigned char   uc;
  signed   short  ss;
  unsigned short  us;
  signed   int    si;
  unsigned int    ui;
  signed   long   sl;
  unsigned long   ul;
           float  ff;
           double df;
  } v;
*/

  




#endif /* CLAD_VARIANT_H_INCLUDED */
