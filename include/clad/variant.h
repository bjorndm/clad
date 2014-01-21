#ifndef CLAD_VARIANT_H_INCLUDED
#define CLAD_VARIANT_H_INCLUDED

#include "clad/shared.h"

enum clad_variant_kind {
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

/* Helper macro, this gets boring manually */
#define CLAD_VARIANT_ELEMENT(ENUM, TYPE, NAME) \
  struct { enum ENUM kind; TYPE value; } NAME

#define CLAD_VARIANT_HEADER(ENUM, NAME) \
  struct { enum ENUM kind; } NAME

/* Generic function for generic function pointer. */
typedef void * clad_variant_f(void * arg);

/* Variant type for many current C types.  */
union clad_variant {
  CLAD_VARIANT_HEADER(clad_variant_kind, header);
  CLAD_VARIANT_ELEMENT(clad_variant_kind, unsigned  char  , uc);
  CLAD_VARIANT_ELEMENT(clad_variant_kind, signed    char  , sc);
  CLAD_VARIANT_ELEMENT(clad_variant_kind, unsigned  short , us);
  CLAD_VARIANT_ELEMENT(clad_variant_kind, signed    short , ss);
  CLAD_VARIANT_ELEMENT(clad_variant_kind, unsigned  int   , ui);
  CLAD_VARIANT_ELEMENT(clad_variant_kind, signed    int   , si);
  CLAD_VARIANT_ELEMENT(clad_variant_kind, unsigned  long  , ul);
  CLAD_VARIANT_ELEMENT(clad_variant_kind, signed    long  , sl);
  CLAD_VARIANT_ELEMENT(clad_variant_kind, float           , ff);
  CLAD_VARIANT_ELEMENT(clad_variant_kind, double          , dd);
  CLAD_VARIANT_ELEMENT(clad_variant_kind, void      *     , pv);
  CLAD_VARIANT_ELEMENT(clad_variant_kind, char      *     , pc);
  CLAD_VARIANT_ELEMENT(clad_variant_kind, short     *     , ps);
  CLAD_VARIANT_ELEMENT(clad_variant_kind, int       *     , pi);
  CLAD_VARIANT_ELEMENT(clad_variant_kind, long      *     , pl);
  CLAD_VARIANT_ELEMENT(clad_variant_kind, float     *     , pf);
  CLAD_VARIANT_ELEMENT(clad_variant_kind, double    *     , pd);
  CLAD_VARIANT_ELEMENT(clad_variant_kind, clad_variant_f *, fp);
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
