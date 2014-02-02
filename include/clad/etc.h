#ifndef CLAD_ETC_H_INCLUDED
#define CLAD_ETC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>

#include "clad/bool.h"

/* Some simple numerical comparison, min, max, etc functions. */
int     clad_mini(int one, int two);
double  clad_mind(double one, double two);
float   clad_minf(float one, float two);
int     clad_maxi(int one, int two);
double  clad_maxd(double one, double two);
float   clad_maxf(float one, float two);
int     clad_comparei(int one, int two);
int     clad_compared(double one, double two);
int     clad_comparef(float one, float two);
int     clad_clampi(int value , int min, int max) ;
double  clad_clampd(double value , double min, double max);
float   clad_clampf(float value , float min, float max);
int     clad_outofboundsi(int value, int min, int max);
int     clad_outofboundsd(int value, double min, double max);
int     clad_outofboundsf(int value, float min, float max);


/* Macro: clad_container(PTR, TYPE, MEMBER)
 This macro returns, for the given pointer, a pointer to a containing struct
 of type TYPE, in which PTR is a member named MEMBER. 
 This enables cool ways of type genericity and extension in plain C.
*/

#define clad_container(PTR, TYPE, MEMBER) \
        ((TYPE *)(((char *)(PTR)) - offsetof(TYPE, MEMBER)))

struct clad_listnode;
struct clad_list;

typedef int clad_listnode_compare(clad_listnode * one, clad_ListNode * two);
typedef int clad_listnode_each(clad_listnode * elem, void * data);
typedef int clad_listnode_searchvalue(clad_listnode * elem, void * data);


/* Struct: clad_List_
 * clad_ListNode is a doubly linked list head. 
 * 
 */
struct clad_List_ {
  struct clad_ListNode_ * head;
  struct clad_ListNode_ * tail;
  int                   size;
};


/* Struct: clad_ListNode_
 * clad_ListNode is a doubly linked list node. 
 * 
 */
struct clad_ListNode_ {
  struct clad_ListNode_ * next;
  struct clad_ListNode_ * prev;
};

/* Returns the list node for this list element is part of, 
for the give list element, and data type*/
#define clad_listnode_getdata(LIST, TYPE, MEMBER)     \
        clad_listnode_data(LIST, offsetof(TYPE, MEMBER))

/* Shorthand for INLI_DATA(LIST, DATA, list) */
#define clad_listnode_listdata(LIST, TYPE) inli_getdata(LIST, TYPE, list)

clad_ListNode * clad_listnode_initempty(clad_ListNode * self);
bool   clad_listnode_isempty(clad_ListNode * self);
clad_ListNode * clad_listnode_initall(clad_ListNode * self , clad_ListNode * next , clad_ListNode * prev );
clad_ListNode * clad_listnode_init(clad_ListNode * self);
clad_ListNode * clad_listnode_unlink(clad_ListNode * self);
clad_ListNode * clad_listnode_add(clad_ListNode * self , clad_ListNode * other );
clad_ListNode * clad_listnode_next(clad_ListNode * self );
clad_ListNode * clad_listnode_prev(clad_ListNode * self );
clad_ListNode * clad_listnode_first(clad_ListNode * self );
clad_ListNode * clad_listnode_last(clad_ListNode * self );
clad_ListNode * clad_listnode_push(clad_ListNode * self , clad_ListNode * other );
clad_ListNode * clad_listnode_unshift(clad_ListNode * self , clad_ListNode * other );
clad_ListNode * clad_listnode_shift(clad_ListNode * self );
clad_ListNode * clad_listnode_pop(clad_ListNode * self );

void * clad_listnode_data(clad_ListNode * self , int offset);

clad_ListNode * 
clad_listnode_search(clad_ListNode * self, clad_ListNodeCompare * compare, clad_ListNode * tofind);

clad_ListNode * 
clad_listnode_remove(clad_ListNode * self, clad_ListNodeCompare * compare, clad_ListNode * toremove);

int clad_listnode_each(clad_ListNode * self, clad_ListNodeEach * each, void * data);

clad_ListNode * 
clad_listnode_searchvalue(clad_ListNode * self, clad_ListNodeSearchValue * compare, void * tofind);


clad_List *       clad_list_init  (clad_List *  self);
clad_List *       clad_list_add   (clad_List *  self, clad_ListNode * node);
clad_List *       clad_list_shift (clad_List *  self, clad_ListNode * node);
clad_List *       clad_list_remove(clad_List *  self, clad_ListNode * node);
clad_ListNode *   clad_list_head  (clad_List *  self);
clad_ListNode *   clad_list_tail  (clad_List *  self);
int             clad_list_size  (clad_List *  self);



typedef struct clad_Bitree_ clad_Bitree;

typedef int clad_BitreeCompare(clad_Bitree * one, clad_Bitree * two);


struct clad_Bitree_ {
  struct clad_Bitree_  * up;
  struct clad_Bitree_  * left;
  struct clad_Bitree_  * right;
};

typedef struct clad_Aatree_ clad_Aatree;
typedef int clad_AatreeCompare(clad_Aatree * one, clad_Aatree * two);
typedef int clad_AatreeSetValue(clad_Aatree * to, clad_Aatree * from);
typedef int clad_AatreeCompareKey(clad_Aatree * self, void * key);
typedef void * clad_AatreeGetKey(clad_Aatree * self);


typedef struct clad_AatreeMethods_ clad_AatreeMethods;

struct clad_AatreeMethods_ {
  clad_AatreeCompare    * compare;
  clad_AatreeSetValue   * setvalue;
  clad_AatreeCompareKey * comparekey;
  clad_AatreeCompareKey * getkey;  
};

struct clad_Aatree_ {
  struct clad_Bitree_    tree;
  int                  level;
};


clad_Bitree * 
clad_bitree_initall(clad_Bitree * self, clad_Bitree * left, clad_Bitree * right, 
                  clad_Bitree * up);

clad_Bitree *
clad_bitree_init(clad_Bitree * self);

clad_Bitree *
clad_bitree_left(clad_Bitree * self);

clad_Bitree *
clad_bitree_right(clad_Bitree * self);

clad_Bitree *
clad_bitree_up(clad_Bitree * self);


clad_Bitree *
clad_bitree_up_(clad_Bitree * self, clad_Bitree * newup);
clad_Bitree *
clad_bitree_left_(clad_Bitree * self, clad_Bitree * newleft);

clad_Bitree *
clad_bitree_right_(clad_Bitree * self, clad_Bitree * newright);

bool clad_bitree_isleaf(clad_Bitree * self);

clad_Aatree * 
clad_aatree_initall(clad_Aatree * self, clad_Aatree * left, clad_Aatree * right, 
                  clad_Aatree * up, int level);

clad_Aatree *
clad_aatree_init(clad_Aatree * self);

clad_Aatree *
clad_aatree_left(clad_Aatree * self);

clad_Aatree *
clad_aatree_right(clad_Aatree * self);

clad_Aatree *
clad_aatree_up(clad_Aatree * self);

clad_Aatree *
clad_aatree_left_(clad_Aatree * self, clad_Aatree * other);

clad_Aatree *
clad_aatree_right_(clad_Aatree * self, clad_Aatree * other);

clad_Aatree *
clad_aatree_up_(clad_Aatree * self, clad_Aatree * other);

int clad_aatree_level(clad_Aatree * self);

int clad_aatree_level_(clad_Aatree * self, int newlevel);

bool clad_aatree_isleaf(clad_Aatree * self);

clad_Aatree * clad_aatree_skew(clad_Aatree * self);

clad_Aatree * clad_aatree_split(clad_Aatree * self);

clad_Aatree * clad_aatree_insert(clad_Aatree * self, clad_Aatree * node, 
                             clad_AatreeMethods * methods);
                             
clad_Aatree * clad_aatree_search(clad_Aatree * self, clad_Aatree * node,
                             clad_AatreeMethods * methods);

clad_Aatree * clad_aatree_searchkey(clad_Aatree * self, void * key,
                                clad_AatreeMethods * methods);

clad_Aatree * clad_aatree_leveldownall(clad_Aatree * self);

clad_Aatree * clad_aatree_successor(clad_Aatree * self);

clad_Aatree * clad_aatree_predecessor(clad_Aatree * self);

clad_Aatree * clad_aatree_delete(clad_Aatree * self, clad_Aatree * node, 
                             clad_AatreeMethods * methods);


clad_Aatree * clad_aatree_deletekey(clad_Aatree * self, void * key, 
                                clad_AatreeMethods * methods);

typedef struct clad_Childtree_ clad_Childtree;

/*
 * Struct: clad_Childtree
 * 
 * A clad_Childtree is a tree where every node can have any number of children.
 * 
 */
struct clad_Childtree_ {
  clad_Childtree * parent;
  clad_Childtree * child;  
  clad_Childtree * next;
  clad_Childtree * previous;
};


clad_Childtree *
clad_childtree_initall(clad_Childtree * self, clad_Childtree * parent, clad_Childtree * child,
                    clad_Childtree * next_sibling, clad_Childtree * previous_sibling); 
clad_Childtree * 
clad_childtree_initnull(clad_Childtree * self);
bool 
clad_childtree_isempty(clad_Childtree * self); 
clad_Childtree * 
clad_childtree_parent(clad_Childtree * self); 
clad_Childtree * 
clad_childtree_child(clad_Childtree * self); 
clad_Childtree * 
clad_childtree_next(clad_Childtree * self);
clad_Childtree * 
clad_childtree_lastsibling(clad_Childtree * self);
clad_Childtree * 
clad_childtree_lastchild(clad_Childtree * self);
clad_Childtree * 
clad_childtree_previous(clad_Childtree * self);
clad_Childtree * 
clad_childtree_insertsibling(clad_Childtree * self, clad_Childtree * sibling);
clad_Childtree * 
clad_childtree_appendsibling(clad_Childtree * self, clad_Childtree * sibling);
clad_Childtree * 
clad_childtree_appendchild(clad_Childtree * self, clad_Childtree * child);
void clad_childtree_printgraph(clad_Childtree * self, int level);



typedef struct clad_Var_     clad_Var;
typedef struct clad_VarList_ clad_VarList;

typedef void clad_Function(void);
typedef clad_Function * clad_FunctionPtr;



union clad_VarUnion_ {
  void        * ptr;
  clad_Function * fptr;
  char        * cstr;
  int           i;
  double        d;
};

enum clad_VarEnum_ {
  CLADVAR_NONE   =  0 ,
  CLADVAR_PTR    = 'p',
  CLADVAR_FPTR   = 'P',
  CLADVAR_CSTR   = 's',
  CLADVAR_INT    = 'i',
  CLADVAR_DOUBLE = 'f',
};

struct clad_Var_ {
  enum  clad_VarEnum_  type;
  union clad_VarUnion_ value;
};


struct clad_Var_ clad_var_makeint(int value);
struct clad_Var_ clad_var_makedouble(double value);
struct clad_Var_ clad_var_makeptr(void * value);
struct clad_Var_ clad_var_makecstr(char * value);
struct clad_Var_ clad_var_makefptr(clad_Function * value);

void * clad_var_ptr(clad_Var self);
clad_Function * clad_var_fptr(clad_Var self);
char * clad_var_cstr(clad_Var self);
int clad_var_int(clad_Var self);
double clad_var_double(clad_Var self);

void clad_var_store(clad_Var * self, void * ptr);
clad_Var * clad_var_load(clad_Var * self, int type, void * ptr) ;
clad_Var clad_var_make(int type, void * valptr) ;

int clad_var_toarrayva(int argc, clad_Var argv[], char * fmt, va_list args) ;
int clad_var_toarraylen(int argc, clad_Var argv[], char * fmt, ...);
int clad_var_toarray(clad_Var argv[], char * fmt, ...);
int clad_var_fromarrayva(clad_Var argv[], int argc, va_list args);
int clad_var_fromarray(clad_Var argv[], int argc, ...);


/* a "Stab" is a String Table, that is, a table of void * pointers 
 index by strings. The Stab does not own it's pointers
 but it does own copies of the string keys, which 
 it will clean up when needed. */
typedef struct clad_Stab_ clad_Stab;
typedef struct clad_StabEntry_ clad_StabEntry;

struct clad_StabEntry_ {
  char * key;
  void * value;
};  

struct clad_Stab_ {
  clad_StabEntry * entries;
  int size;
};

clad_Stab * clad_stab_init(clad_Stab * self);
clad_Stab * clad_stab_done(clad_Stab * self);
void * clad_stab_put(clad_Stab * self, char * key, void * value);   
void * clad_stab_get(clad_Stab * self, char * key);   


void * clad_gar_new(size_t nmemb, size_t size);
void * clad_gar_resize(void ** arr, size_t *  nmemb, size_t size, int delta);
void * clad_gar_get(void * arr, size_t nmemb, size_t size, size_t index);
void * clad_gar_put(void * arr, size_t nmemb, size_t size, size_t index, void * data);
void * clad_gar_free(void * arr);

void * clad_par_new(size_t nmemb);
void * clad_par_resize(void ** arr, size_t * nmemb, int delta);
void * clad_par_get(void * arr, size_t nmemb, size_t index);
void * clad_par_put(void * arr, size_t nmemb, size_t index, void * data);
void * clad_par_free(void * arr);


#endif /* CLAD_H_INCLUDED */