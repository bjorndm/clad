
#include "clad/bool.h"
#include "clad/variant.h"



CLAD_API union clad_variant clad_variant_from_int(int value) {
  union clad_variant me; 
  me.si.type  = CLAD_VARIANT_SIGNED_INT;
  me.si.value = value;
  return me;
}

CLAD_API int clad_variant_to_int(union clad_variant me, int * value) {
  if(!value) return CLAD_FALSE;
  if(me.none.type != CLAD_VARIANT_SIGNED_INT) return CLAD_FALSE;
  (*value) = me.si.value;
  return CLAD_TRUE;
}

