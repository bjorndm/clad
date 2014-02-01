
#ifndef CLAD_NSE_H_INCLUDED
#define CLAD_NSE_H_INCLUDED

#include "clad/pp.h"

/*

Clad namespace emulation. This requires the declaration of 
API structs with type names that end in _api and implementation 
names that end in _implementation names.

This macro provides pure syntactic sugar. It's almost as easy to do 
this manually, but the macros express the intent somewhat more clearly.

*/

#define CLAD_NSE_API_OF(NS)  CLAD_PP_PASTE(NS, _api)
#define CLAD_NSE_IMPL_OF(NS) CLAD_PP_PASTE(NS, _implementation)
#define CLAD_NSE_USING(NS, AS)                            \
        static const struct CLAD_NSE_API_OF(NS) * (AS)=   \
        &CLAD_NSE_IMPL_OF(NS)

#ifndef USING
  #define USING(NS, AS) CLAD_NSE_USING(NS, AS)
#endif

#endif