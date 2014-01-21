/**
Unfortunately, because clad is C89, we must define our own boolean type 
as well, together with our own true and false.
*/
#ifndef CLAD_BOOL_H_INCLUDED
#define CLAD_BOOL_H_INCLUDED

typedef int clad_bool;

enum {
  CLAD_FALSE = 0,
  CLAD_TRUE  = !CLAD_FALSE,
} clad_bool_enum;

#endif





