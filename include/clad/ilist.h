#ifndef clad_ilist_H_INCLUDED
#define clad_ilist_H_INCLUDED

/**
* The struct clad_ilist is an intrusive doubly linked list.
* Intrusive means that it should be stored into it's list elements, 
* the reference to the element can b gotten though the offsetof() macro.
*/

struct clad_ilist {
  struct clad_ilist * next;
  struct clad_ilist * prev;
};

/** Returns the list node for this list element is part of, 
for the given list element, and data type*/
#define CLAD_ILIST_DATA(LIST, TYPE, MEMBER)  \
        (((char *)LIST) - offsetof(TYPE, MEMBER))

struct clad_ilist * 
clad_ilist_initall(struct clad_ilist * self,
                   struct clad_ilist * next,
                   struct clad_ilist * prev);

struct clad_ilist * 
clad_ilist_init(struct clad_ilist * self);

struct clad_ilist * 
clad_ilist_remove(struct clad_ilist * self);

struct clad_ilist * 
clad_ilist_append(struct clad_ilist * self, struct clad_ilist * other);

struct clad_ilist * 
clad_ilist_prepend(struct clad_ilist * self, struct clad_ilist * other);


struct clad_ilist *
clad_ilist_next (struct clad_ilist * self);

struct clad_ilist *
clad_ilist_prev (struct clad_ilist * self);

struct clad_ilist *
clad_ilist_first (struct clad_ilist * self);

struct clad_ilist *
clad_ilist_last (struct clad_ilist * self);

struct clad_ilist *
clad_ilist_push (struct clad_ilist * self, struct clad_ilist * other);

struct clad_ilist *
clad_ilist_unshift(struct clad_ilist * self, struct clad_ilist * other );

struct clad_ilist *
clad_ilist_shift(struct clad_ilist * self);

struct clad_ilist *
clad_ilist_pop(struct clad_ilist * self);



#endif




