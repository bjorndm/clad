
#ifndef CLAD_MACRO_H_INCLUDED
#define CLAD_MACRO_H_INCLUDED

/* This header file contains some utility preprocessor macros of general use 
and for the use of CLAD. */

/* Helper macro for the use of CLAD_PP_STRINGIFY. */
#define CLAD_PP_TOSTR_AID(VAL)            #VAL

/* Helper macro for the use of CLAD_PP_PASTE. */
#define CLAD_PP_PASTE_AID(ARG1, ARG2)     ARG1##ARG2

/** Stringify the given argument. */
#define CLAD_PP_TOSTR(VAL)                CLAD_PP_TOSTR_AID(VAL)

/** Token pastes the given arguments. */
#define CLAD_PP_PASTE(ARG1, ARG2)         CLAD_PP_PASTE_AID(ARG1, ARG2)

/** Concatenates two string constants together */
#define CLAD_PP_JOINSTR(ARG1, ARG2)       (ARG1 ARG2)

/** Concatenates three string constants together */
#define CLAD_PP_JOINSTR3(A1, A2, A3)      (A1 A2 A3)

/** Returns __LINE__ as a string. */
#define CLAD_PP_LINE_STR()                CLAD_PP_TOSTR(__LINE__)

/** Returns __FILE__ as a string. */
#define CLAD_PP_FILE_STR()                CLAD_PP_TOSTR(__FILE__)

/** Returns __line__ in the form " line nr: 1234" */
#define CLAD_PP_LONGLINE_STR()            \
          PP_JOINSTR(" line nr:", PP_LINE_STR())

/** Prevents spurious unused variable or function compiler warnings. */
#define CLAD_UNUSED(x) ((void)(x))








#endif

