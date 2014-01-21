/**
* This file contains macros that are needed to portably implement 
* shared libraries or DLL's. Trouble maker here is MSVC which requires
* those silly __declspec(dllexport) and __declspec(dllimport) to export
* or import functions in dlls.
*/

#ifndef CLAD_SHARED_H_INCLUDED
#define CLAD_SHARED_H_INCLUDED

#include "clad/platform.h"


/** Get some help from cmake to see if a dll is being built on Windows. */
#ifdef clad_EXPORTS
  #ifndef CLAD_BUILD_SHARED_LIBRARY
    #define CLAD_BUILD_SHARED_LIBRARY
  #endif
#endif

/** Use the macro CLAD_API to mark all functions that should go into 
a shared library or dll when it is compiled. */
#if defined (_WIN32)
  #ifdef CLAD_BUILD_SHARED_LIBRARY
    #define CLAD_API __declspec(dllexport)
  #else
    #define CLAD_API __declspec(dllimport)
  #endif /* _CLAD_BUILD_SHARED_LIBRARY */
#else
  #define CLAD_API
#endif /* _WIN32 */



#endif /* CLAD_SHARED_H_INCLUDED */
