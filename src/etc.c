#include <string.h>
#include "clad/etc.h"

int clad_mini(int one, int two) {
  return (one < two) ? one : two;  
}

double clad_mind(double one, double two) {
  return (one < two) ? one : two;  
}

float clad_minf(float one, float two) {
  return (one < two) ? one : two;  
}


int clad_maxi(int one, int two) {
  return (one > two) ? one : two;  
}

double clad_maxd(double one, double two) {
  return (one > two) ? one : two;
}

float clad_maxf(float one, float two) {
  return (one > two) ? one : two;
}



int clad_comparei(int one, int two) {
  if (one < two) return -1;
  if (one > two) return  1;
  return 0;
}

int clad_compared(double one, double two) {
  if (one < two) return -1;
  if (one > two) return  1;
  return 0;
}

int clad_comparef(float one, float two) {
  if (one < two) return -1;
  if (one > two) return  1;
  return 0;
}


int clad_clampi(int value , int min, int max) {
  if (value < min) return min;
  if (value > max) return max;
  return value;
}


double clad_clampd(double value , double min, double max) {
  if (value < min) return min;
  if (value > max) return max;
  return value;
}


float clad_clampf(float value , float min, float max) {
  if (value < min) return min;
  if (value > max) return max;
  return value;
}

int clad_outofboundsi(int value, int min, int max) {
  if (value < min)  return TRUE;
  return (value >= max); 
}


int clad_outofboundsd(int value, double min, double max) {
  if (value < min)  return TRUE;
  return (value >= max); 
}

int clad_outofboundsf(int value, float min, float max) {
  if (value < min)  return TRUE;
  return (value >= max); 
}



/**
* Struct: clad_ListNode
*
* clad_ListNode is an intrusive doubly linked list.
* These lists do not contain any pointers to the data member that is part of 
* the list, rather, you use them by including them into the struct that 
* needs to be included in the intrusive linked list, hence the "intrusive".
* Use the macro clad_container to get the containing struct back.
*
* For example : struct Foo { int value ; clad_ListNode list } ...
* struct Foo foo, bar; clad_listnode_init(&foo.list); clad_listnode_init(&bar.list);
* clad_listnode_add(&foo.list, &bar.list);
* 
*/

/**
* Function: clad_listnode_initall
*
* Fully initializes a non-NULL intrusive linked list.
*
* Parameters:
*   self - clad_ListNode to initialize
*   next - Next clad_ListNode list node to link to or NULL
*   prev - Previous clad_ListNode list node to link to or NULL
*
* Returns: 
*   self
*/
clad_ListNode * clad_listnode_initall(clad_ListNode * self, clad_ListNode * next, clad_ListNode * prev) {
  if (!self) return NULL;
  self->next = next;
  self->prev = prev;
  return self;
}

/**
* Function: clad_listnode_init
*
* Initializes the intrusive linked list. Next and prev are set to NULL.
*
* Parameters:
*   self - clad_ListNode to initialize
*
* Returns: 
*   self
*/
clad_ListNode * clad_listnode_init(clad_ListNode * self) {
  return clad_listnode_initall(self, NULL, NULL);
}


/**
* Function: clad_listnode_initempty
*
* Initializes the intrusive linked list to be empty. Next is set to self
* to signal this to clad_listnode_isempty.
*
* Parameters:
*   self - clad_ListNode to initialize as empty
*
* Returns: 
*   self
*/
clad_ListNode * clad_listnode_initempty(clad_ListNode * self) {
  return clad_listnode_initall(self, self, NULL);
}

/**
* Function: clad_listnode_isempty
*
* Returns true if the list is empty, false if not.
* 
* Parameters:
*   self - clad_ListNode to check.
*
* Returns: 
*   TRUE if empty, FALSE if not. A NULL list is also empty.
*/
bool clad_listnode_isempty(clad_ListNode * self) {
  if(!self) return TRUE;  
  return clad_listnode_next(self) == self;
}


/** 
* Function: clad_listnode_unlink
*
* Unlinks self from the list it is part of. 
* Does NOT clean up any data asssociated with the container of the intrusive 
* list and also doesn't free self, since self should be part of the container 
* of the intrusive list. 
*
* Parameters:
*   self - clad_ListNode to remove from whole of list. May be NULL.
*
* Returns: 
*   self
*/
clad_ListNode * clad_listnode_unlink(clad_ListNode * self) {  
  if(!self) return NULL;
  if(self->prev) { self->prev->next = self->next; }
  if(self->next) { self->next->prev = self->prev; }
  self->prev = NULL;
  self->next = NULL;
  return self;
}

/** 
* Function: clad_listnode_add
*
* Appends other after self. 
*
* Parameters:
*   self - clad_ListNode to append to. IF NULL, returns other, since that becomes 
*          the base of the list.
*   other - clad_ListNode to append to self.
*
* Returns:
*   The new "first" element of the list.
*/
clad_ListNode * clad_listnode_add(clad_ListNode * self, clad_ListNode * other) {  
  if(!self)  return other;
  if(!other) return self;
  self->next  = other;
  other->prev = self;
  return other;
}

/** 
* Function: clad_listnode_next
*
* Returns the next element in the list
*
* Parameters:
*   self - clad_ListNode
*
* Returns: 
*   the next element in the list, or NULL if no next item. 
*/
clad_ListNode * clad_listnode_next(clad_ListNode * self) {
  if(!self) return NULL;
  return self->next;
}

/** 
* Function: clad_listnode_prev
*
* Returns the previous element in the list
*
* Parameters:
*   self - clad_ListNode
*
* Returns: 
*   the next element in the list, or NULL if no next item. 
*/
clad_ListNode * clad_listnode_prev(clad_ListNode * self) {
  if(!self) return NULL;
  return self->prev;
}

/** 
* Function: clad_listnode_first
*
* Returns the first element in the list, by dumb iteration.
*
* Parameters:
*   self - clad_ListNode
*
* Returns: 
*   the first link in the list, or NULL if self is NULL. 
*/
clad_ListNode * clad_listnode_first(clad_ListNode * self) {
  clad_ListNode * aid = self; 
  if(!aid) return NULL;
  while (aid->prev) {
    aid = aid->prev;
  }
  return aid;  
}

/** 
* Function: clad_listnode_last
*
* Returns the last element in the list, by dumb iteration.
*
* Parameters:
*   self - clad_ListNode
*
* Returns: 
*   the last link in the list, or NULL if self is NULL. 
*/
clad_ListNode * clad_listnode_last(clad_ListNode * self) {
  clad_ListNode * aid = self; 
  if(!aid) return NULL;
  while (aid->next) {
    aid = aid->next;
  }
  return aid;  
}

/** 
* Function: clad_listnode_push
*
* Appends other to the end of the list by dumb iteration.
*
* Parameters:
*   self - clad_ListNode
*
* Returns: 
*   other, or NULL if self or other is NULL. 
*/
clad_ListNode * clad_listnode_push(clad_ListNode * self, clad_ListNode * other) {  
  clad_ListNode * aid;
  aid = clad_listnode_last(self);
  return clad_listnode_add(aid, other);
}


/** 
* Function: clad_listnode_unshift 
*                
* Prepends other to the beginning of the list by dumb iteration.
*
* Parameters:
*   self - clad_ListNode
*
* Returns: 
*   other, or NULL if self or other is NULL. Other is now also the new 
*   beginning of the list.
*/
clad_ListNode * clad_listnode_unshift(clad_ListNode * self, clad_ListNode * other) {  
  clad_ListNode * aid;
  aid = clad_listnode_first(self);
  clad_listnode_add(other, aid);
  return other;
}


/** 
* Function: clad_listnode_shift
*
* Removes the first element from the list by dumb iteration.
*
* Parameters:
*   self - clad_ListNode
*
* Returns: 
*   list node that was removed, or NULL if self is NULL. 
*/
clad_ListNode * 
clad_listnode_shift(clad_ListNode * self) {  
  clad_ListNode * aid;
  aid = clad_listnode_first(self);
  return clad_listnode_unlink(aid);
}


/** 
* Function: clad_listnode_pop
*
* Removes the last element from the list by dumb iteration.
*
* Parameters:
*   self - clad_ListNode
*
* Returns: 
*   list node that was removed, or NULL if self is NULL. 
*/
clad_ListNode * 
clad_listnode_pop(clad_ListNode * self) {  
  clad_ListNode * aid;
  aid = clad_listnode_last(self);
  return clad_listnode_unlink(aid);
}


/** 
* Function: clad_listnode_data
* 
* Parameters:
* self - list node to get the data of.
* offset - Use offsetof to calculate this offset.
*
* Returns:  
*   the data for this node of the singly linked list. 
* 
*/
void * 
clad_listnode_data(clad_ListNode * self, int offset) {
  if(!self) return NULL;
  return (void *)((char *)self - offset);
}



/** 
* Function: clad_listnode_search
* 
* Parameters:
* self   - list node to search.
* offset - Comparer function, get passed each element of the clad_ListNode * and 
*          tofind, must return 0 if the item searched for is found.
*
* Returns:  
*   the clad_ListNode found, or NULL if not found.
* 
*/
clad_ListNode * 
clad_listnode_search(clad_ListNode * self, clad_ListNodeCompare * compare, clad_ListNode * tofind) {
  clad_ListNode * aid;
  if (clad_listnode_isempty(self)) return NULL;
  for(aid = self; aid ; aid = aid->next) {
    int cmp = compare(aid, tofind);
    if (cmp == 0) return aid;
  }
  return NULL;
}

/** 
* Function: clad_listnode_searchvalue
* 
* Parameters:
* self   - list node to search.
* offset - Comparer function, get passed each element of the clad_ListNode * and 
*          tofind, must return 0 if the item searched for is found.
* tofind - Arbitrary pointer to a VALUE (not a clad_ListNode *).
* Returns:  
*   the clad_ListNode found, or NULL if not found.
* 
*/
clad_ListNode * 
clad_listnode_searchvalue(clad_ListNode * self, clad_ListNodeSearchValue * compare, void * tofind) {
  clad_ListNode * aid;
  if (clad_listnode_isempty(self)) return NULL;
  for(aid = self; aid ; aid = aid->next) {
    int cmp = compare(aid, tofind);
    if (cmp == 0) return aid;
  }
  return NULL;
}

/*
* Function: clad_listnode_unlink
*
* A shorthand for clad_listnode_unlink(clad_listnode_search(self, compare, toremove));
*/
clad_ListNode * 
clad_listnode_remove(clad_ListNode * self, clad_ListNodeCompare * compare, clad_ListNode * toremove) {  
  return clad_listnode_unlink(clad_listnode_search(self, compare, toremove));
}


/*
 * Function: clad_listnode_each
 * 
 * Iterates over all list elements starting from self. 
 * It's safe to unlink the element passed to clad_ListNodeEach. 
 * The iteration stops if clad_ListNodeEach returns non-zero.
 */
int clad_listnode_each(clad_ListNode * self, clad_ListNodeEach * each, void * data) {
  clad_ListNode * aid, * next;
  int res = 0;
  aid = self;
  while(aid) {
    next = clad_listnode_next(aid);
    res  = each(aid, data);
    if(res) return res;
    aid  = next;
  }
  return res;
}


clad_List * clad_list_init(clad_List * self) {
  if (!self) return NULL;
  self->head = NULL;
  self->tail = NULL;
  self->size = 0;
  return self;
}

clad_List * clad_list_add(clad_List * self, clad_ListNode * node) {
  if (!self) return NULL;
  if (!self->tail) { 
    self->head       = node;
    clad_listnode_initall(node, NULL, NULL);
  } else {      
    self->tail->next = node;
    node->prev       = self->tail;
    node->next       = NULL;
  }
  self->tail         = node;
  self->size++;
  return self;
}

clad_List * clad_list_shift(clad_List * self, clad_ListNode * node) {
  if (!self) return NULL;
  if (!self->head) { 
    self->tail       = node;
    clad_listnode_initall(node, NULL, NULL);
  } else {      
    self->head->prev = node;
    node->prev       = NULL;
    node->next       = self->head;
  }
  self->head         = node;
  self->size++;
  return self;
}


clad_List * clad_list_remove(clad_List * self, clad_ListNode * node) {
  if(self->tail == node) {
    self->tail = node->prev;
  } 
  if(self->head == node) {
    self->head = node->next;
  } 
  if (!self->tail) { self->head = NULL; }  
  if (!self->head) { self->tail = NULL; }
  clad_listnode_unlink(node);
  self->size--;
  return self;
}


clad_ListNode * clad_list_head(clad_List * self) {
  if (!self) return NULL;
  return self->head;
}

clad_ListNode * clad_list_tail(clad_List * self) {
  if (!self) return NULL;
  return self->tail;
}

int clad_list_size(clad_List * self) {
  if (!self) return 0;
  return self->size;
}


clad_Bitree * 
clad_bitree_initall(clad_Bitree * self, clad_Bitree * left, clad_Bitree * right, 
                  clad_Bitree * up) {
  if(!self) return NULL;
  self->left  = left;
  self->right = right;
  self->up    = up;
  return self;
}

clad_Bitree *
clad_bitree_init(clad_Bitree * self) {
  return clad_bitree_initall(self, NULL, NULL, NULL);
}

clad_Bitree *
clad_bitree_left(clad_Bitree * self) {
  if(!self) return NULL;
  return self->left;
}

clad_Bitree *
clad_bitree_right(clad_Bitree * self) {
  if(!self) return NULL;
  return self->right;
}

clad_Bitree *
clad_bitree_up(clad_Bitree * self) {
  if(!self) return NULL;
  return self->right;
}


clad_Bitree *
clad_bitree_up_(clad_Bitree * self, clad_Bitree * newup) {
  if(!self) return NULL;
  return self->up = newup;
}

clad_Bitree *
clad_bitree_left_(clad_Bitree * self, clad_Bitree * newleft) {
  if(!self) return NULL;
  clad_bitree_up_(newleft, self);
  return self->left = newleft;
}

clad_Bitree *
clad_bitree_right_(clad_Bitree * self, clad_Bitree * newright) {
  if(!self) return NULL;
  clad_bitree_up_(newright, self);
  return self->right = newright;
}

bool clad_bitree_isleaf(clad_Bitree * self) {
  if(!self) return FALSE;
  if(clad_bitree_right(self)) return FALSE;
  if(clad_bitree_left(self)) return FALSE;
  return TRUE;
}


clad_Aatree * 
clad_aatree_initall(clad_Aatree * self, clad_Aatree * left, clad_Aatree * right, 
                  clad_Aatree * up, int level) {
  if(!clad_bitree_initall(&self->tree, &left->tree, &right->tree, &up->tree)) 
    return NULL;
  self->level = level;
  return self;
}

clad_Aatree *
clad_aatree_init(clad_Aatree * self) {
  return clad_aatree_initall(self, NULL, NULL, NULL, 1);
}

#define clad_bi2aa(PTR) clad_container(PTR, clad_Aatree, tree)

clad_Aatree *
clad_aatree_left(clad_Aatree * self) {
  if(!self) return NULL;
  return clad_bi2aa(clad_bitree_left(&self->tree));
}

clad_Aatree *
clad_aatree_right(clad_Aatree * self) {
  if(!self) return NULL;
  return clad_bi2aa(clad_bitree_right(&self->tree));
}

clad_Aatree *
clad_aatree_up(clad_Aatree * self) {
  if(!self) return NULL;
  return clad_bi2aa(clad_bitree_up(&self->tree));
}

clad_Aatree *
clad_aatree_left_(clad_Aatree * self, clad_Aatree * other) {
  if(!self) return NULL;
  return clad_bi2aa(clad_bitree_left_(&self->tree, &other->tree));
}

clad_Aatree *
clad_aatree_right_(clad_Aatree * self, clad_Aatree * other) {
  if(!self) return NULL;
  return clad_bi2aa(clad_bitree_right_(&self->tree, &other->tree));
}

clad_Aatree *
clad_aatree_up_(clad_Aatree * self, clad_Aatree * other) {
  if(!self) return NULL;
  return clad_bi2aa(clad_bitree_up_(&self->tree, &other->tree));
}

int clad_aatree_level(clad_Aatree * self) { 
  if(!self) return -1;
  return self->level;
}

int clad_aatree_level_(clad_Aatree * self, int newlevel) { 
  if(!self) return -1;
  return self->level = newlevel;
}

bool clad_aatree_isleaf(clad_Aatree * self) {
  if(!self) return FALSE;
  return clad_bitree_isleaf(&self->tree);
}

clad_Aatree * clad_aatree_skew(clad_Aatree * self) { 
  clad_Aatree * left, * leftleft;
  if(!self) return NULL;
  left        = clad_aatree_left(self);
  if(!left) return self;
  leftleft    = clad_aatree_left(left);
  if(!leftleft) return self;
  if(clad_aatree_level(self) == clad_aatree_level(leftleft)) {
    clad_Aatree * left = clad_aatree_left(self);
    clad_aatree_left_(self, clad_aatree_right(left));
    clad_aatree_right_(left, self);
    return left;
  }
  return self;
}

clad_Aatree * clad_aatree_split(clad_Aatree * self) { 
  clad_Aatree * right, * rightright;
  if(!self) return NULL;
  right       = clad_aatree_right(self);
  if(!right) return self;
  rightright  = clad_aatree_right(right);
  if(!rightright)             return self;
  if (clad_aatree_level(self) == clad_aatree_level(rightright)) {
    clad_aatree_right_(self, clad_aatree_left(right));
    clad_aatree_left_(right, self);
    clad_aatree_level_(right, clad_aatree_level(right) + 1);
    return right;
  }
  return self;
}

clad_Aatree * clad_aatree_insert(clad_Aatree * self, clad_Aatree * node, 
                             clad_AatreeMethods * methods) { 
  int cmp;
  clad_Aatree * aid; 
  if(!self) { return node; } 
  cmp = methods->compare(self, node);
  if(cmp < 0) {
    aid = clad_aatree_insert(clad_aatree_left(self), node, methods);
    clad_aatree_left_(self, aid);
  } else if (cmp > 0) {
    aid = clad_aatree_insert(clad_aatree_right(self), node, methods);
    clad_aatree_right_(self, aid);
  } else { /* Ignore duplicates for now,... */
  }
  self = clad_aatree_skew(self);
  self = clad_aatree_split(self);
  return self;
}

clad_Aatree * clad_aatree_search(clad_Aatree * self, clad_Aatree * node,
                             clad_AatreeMethods * methods) { 
  int cmp;
  clad_Aatree * aid; 
  if(!self) { return NULL; } 
  cmp = methods->compare(self, node);
  if(cmp < 0) {
    return clad_aatree_search(clad_aatree_left(self), node, methods);
  } else if (cmp > 0) {
    return clad_aatree_search(clad_aatree_right(self), node, methods);
  } else { /* Found the item! */
    return self;
  }
}


clad_Aatree * clad_aatree_leveldownall(clad_Aatree * self) {
  clad_Aatree * right = clad_aatree_right(self);
  int lowest = clad_mini(clad_aatree_level(self), clad_aatree_level(right)) + 1;
  if (lowest < clad_aatree_level(self)) {
    clad_aatree_level_(self, lowest);
    if (lowest < clad_aatree_level(right)) {
      clad_aatree_level_(right, lowest);
    }
  }
  return self;
}

clad_Aatree * clad_aatree_successor(clad_Aatree * self) {
  clad_Aatree * aid, *next;
  if(!self) return NULL;
  aid  = clad_aatree_right(self); 
  if(!aid) return NULL;
  next = clad_aatree_left(aid);
  while (next) {
    aid  = next;
    next = clad_aatree_left(aid); 
  };
  return aid;
}

clad_Aatree * clad_aatree_predecessor(clad_Aatree * self) {
  clad_Aatree * aid, *next;
  if(!self) return NULL;
  aid  = clad_aatree_left(self); 
  if(!aid) return NULL;
  next = clad_aatree_right(aid);
  while (next) {
    aid  = next;
    next = clad_aatree_right(aid); 
  };
  return aid;
}

clad_Aatree * clad_aatree_delete(clad_Aatree * self, clad_Aatree * node, 
                             clad_AatreeMethods * methods) {
  clad_Aatree * aid;
  int cmp;
  if(!self) { return self; } 
  cmp = methods->compare(self, node);
  if(cmp < 0) {
    aid = clad_aatree_delete(clad_aatree_left(self), node, methods);
    clad_aatree_left_(self, aid);
  } else if (cmp > 0) {
    aid = clad_aatree_delete(clad_aatree_right(self), node, methods);
    clad_aatree_right_(self, aid);
  } else { /* Found the value ! */
    if(clad_aatree_isleaf(self)) {
      clad_aatree_init(self); /* call init to unlink the tree's up pointer. */
      return NULL;
    } else if (!clad_aatree_left(self)) {
      clad_Aatree * 
      left  = clad_aatree_successor(self);
      aid   = clad_aatree_delete(left, clad_aatree_right(self), methods);
      clad_aatree_right_(self, aid);
      methods->setvalue(self, left);
    } else {
      clad_Aatree * 
      right = clad_aatree_predecessor(self);
      aid   = clad_aatree_delete(right, clad_aatree_left(self), methods);
      clad_aatree_left_(self, aid);
      methods->setvalue(self, right);
    }
  }
  /* Rebalance */
  clad_aatree_leveldownall(self);
  self  = clad_aatree_skew(self);
  aid   = clad_aatree_right(self);
  aid   = clad_aatree_skew(aid);
  clad_aatree_right_(self, aid);
  aid   = clad_aatree_right(clad_aatree_right(self));
  aid   = clad_aatree_skew(aid);
  clad_aatree_right_(clad_aatree_right(self), aid);
  self  = clad_aatree_split(self);
  aid   = clad_aatree_right(self);
  aid   = clad_aatree_skew(aid);
  clad_aatree_right_(self, aid);
  return self;
}

void clad_aatree_printgraph(clad_Aatree * self, int level) {
  if(level == 0) {
    printf("digraph { \n");
  }
  level++;
  if(clad_aatree_left(self)) { 
    printf("t%p -> t%p [color=red];\n", self, clad_aatree_left(self));
    clad_aatree_printgraph(clad_aatree_left(self), level);
  }
  if(clad_aatree_right(self)) {
    printf("t%p -> t%p [color=green];\n", self, clad_aatree_right(self));
    clad_aatree_printgraph(clad_aatree_right(self), level);
  }
  level--;
  if(level == 0) {
    printf("} \n");
  }
}

clad_Childtree *
clad_childtree_initall(clad_Childtree * self, clad_Childtree * parent, clad_Childtree * child,
                    clad_Childtree * next_sibling, clad_Childtree * previous_sibling) {
 if(!self) return NULL;
 self->parent           = parent;
 self->child            = child;
 self->next             = next_sibling;
 self->previous         = previous_sibling;
 return self;
}

clad_Childtree * 
clad_childtree_initnull(clad_Childtree * self) {
  return clad_childtree_initall(self, NULL, NULL, NULL, NULL);
}

/* An empty clad_childtree is simply a NULL tree. */
bool 
clad_childtree_isempty(clad_Childtree * self) {
  return !self;
}
  
clad_Childtree * 
clad_childtree_parent(clad_Childtree * self) {
  if (clad_childtree_isempty(self)) return NULL;
  return self->parent;
}


clad_Childtree * 
clad_childtree_child(clad_Childtree * self) {
  if (clad_childtree_isempty(self)) return NULL;
  return self->child;
}


clad_Childtree * 
clad_childtree_next(clad_Childtree * self) {
  if (clad_childtree_isempty(self)) return NULL;
  return self->next;
}

/* Returns the last sibling of self, or NULL if no siblings or if self is NULL. */
clad_Childtree * 
clad_childtree_lastsibling(clad_Childtree * self) {
  clad_Childtree * aid, * next; 
  if (clad_childtree_isempty(self)) return NULL;
  aid   = self;
  next  = clad_childtree_next(aid);
  /* Skip until the end of the list. */
  while(next) {
    aid   = next;
    next  = clad_childtree_next(aid);
  }
  return aid;
}

/* Returns the last child of the tree, or NULL if no children or nself is NULL. */
clad_Childtree * 
clad_childtree_lastchild(clad_Childtree * self) {
  if (clad_childtree_isempty(self)) return NULL;
  return clad_childtree_lastsibling(self->child);
}


/* Returns the previous sibling of self or NULL if no previous child. */
clad_Childtree * 
clad_childtree_previous(clad_Childtree * self) {
  if (clad_childtree_isempty(self)) return NULL;
  return self->previous;
}


/* Inserts the sibling as a sibling of self, right after self. Sets parent
 link of the sibling too. */
clad_Childtree * 
clad_childtree_insertsibling(clad_Childtree * self, clad_Childtree * sibling) {
  clad_Childtree * next;
  if (clad_childtree_isempty(self)) return sibling;  
  if (clad_childtree_isempty(sibling)) return self;  
  next                          = self->next; 
  self->next                    = sibling;
  sibling->next                 = next;
  sibling->previous             = self;
  if (next) {
    next->previous              = sibling;    
  }
  sibling->parent               = self->parent;
  return self;
}

/* Appends sibling as the last sibling of self. 
 * Returns the new root element of the tree. If self is NULL, sibling is 
 * returned as that will be the new root of the clad_Childtree. 
 */
clad_Childtree * 
clad_childtree_appendsibling(clad_Childtree * self, clad_Childtree * sibling) {
  clad_Childtree * last;
  if (clad_childtree_isempty(self)) return sibling;
  last = clad_childtree_lastsibling(self);
  if(!last) {
    last = self; 
  }
  clad_childtree_insertsibling(last, sibling);  
  return self;
}


/* Appends child as the last child sibling of self. 
 * Returns the new root element of the tree. If self is NULL, child is 
 * returned as that will be the new root of the clad_Childtree. 
 */
clad_Childtree * 
clad_childtree_appendchild(clad_Childtree * self, clad_Childtree * child) {
  clad_Childtree * last;
  if (clad_childtree_isempty(self)) return child;
  last = clad_childtree_lastchild(self);
  if(!last) {
    self->child = child;
  } else { 
    clad_childtree_insertsibling(last, child);
  }
  child->parent = self;
  return self;
} 



/* Shows the tree in a text form on stdout, suitable for dot to concert to a graph. 
 */
void clad_childtree_printgraph(clad_Childtree * self, int level) {
  clad_Childtree * aid; 
  if(level == 0) {
    printf("digraph { \n");
  }
  level++;
  for (aid = clad_childtree_child(self) ; aid ; aid = clad_childtree_next(aid)) { 
    printf("t%p -> t%p [color=red];\n", self, aid);
    if (clad_childtree_parent(aid) == self) {
      printf("t%p -> t%p [color=blue];\n", aid, clad_childtree_parent(aid));
    }    
    clad_childtree_printgraph(aid, level);
  }
  level--;
  if(level == 0) {
    printf("} \n");
  }
}




/* Playing with a boxed C pointer. Avoids double frees or unintentional reuse.
*/
struct clad_Boxptr_ {
  void * ptr_private;  
};


struct clad_Boxptr_ clad_boxptr_make(void * ptr) {
  struct clad_Boxptr_ self = {ptr};
  return self;
}

struct clad_Boxptr_ clad_boxptr_malloc(size_t size) {
  return clad_boxptr_make(malloc(size));
}

void * clad_boxptr_borrow(struct clad_Boxptr_ * self) {
  return self->ptr_private;
} 

int clad_boxptr_isnull(struct clad_Boxptr_ * self) {
  return (!self->ptr_private);
} 

void * clad_boxptr_index(struct clad_Boxptr_ * self, size_t offset) {
  if(clad_boxptr_isnull(self)) return NULL;
  return self->ptr_private + offset;
} 

void * clad_boxptr_rindex(struct clad_Boxptr_ * self, size_t offset) {
  if(clad_boxptr_isnull(self)) return NULL;
  return self->ptr_private - offset;
} 


/* Takes ownership of data from box pointer "from". 
 * From box pointer will be set to NULL. 
 */
struct clad_Boxptr_ * clad_boxptr_own(struct clad_Boxptr_ * self, struct clad_Boxptr_ * from) {
  self->ptr_private = from->ptr_private;
  from->ptr_private = NULL;
  return self->ptr_private;
} 


struct clad_Boxptr_ * 
clad_boxptr_realloc(struct clad_Boxptr_ * self, size_t size) {
  void * old = self->ptr_private;
  void * aid = realloc(old, size);
  if(aid) { self->ptr_private = aid; }
  return self;
}

void
clad_boxptr_free(struct clad_Boxptr_ * self) {
  free(self->ptr_private);
  self->ptr_private = NULL;
}

/* Another more simple approach, but you cannot forget o use 
 * clad_xfree(&pointer), then...
 */
void clad_xfree(void ** ptrptr) {
  if(!ptrptr) return;
  free(*ptrptr);
  (*ptrptr) = NULL;
}

void* clad_xrealloc(void ** ptrptr, size_t size) {
  void*aid;
  if(!ptrptr) return NULL;
  aid = realloc(*ptrptr,size);
  if(aid) {
    (*ptrptr) = aid;
  }
  return aid;
}




struct clad_Var_ clad_var_makeint(int value) {
  struct clad_Var_ result;
  result.type    = BADVAR_INT;
  result.value.i = value;
  return result;
}

struct clad_Var_ clad_var_makedouble(double value) {
  struct clad_Var_ result;
  result.type      = BADVAR_DOUBLE;
  result.value.d   = value;
  return result;
}

struct clad_Var_ clad_var_makeptr(void * value) {
  struct clad_Var_ result;
  result.type      = BADVAR_PTR;
  result.value.ptr = value;
  return result;
}


struct clad_Var_ clad_var_makecstr(char * value) {
  struct clad_Var_ result;
  result.type      = BADVAR_PTR;
  result.value.ptr = value;
  return result;
}

struct clad_Var_ clad_var_makefptr(clad_Function * value) {
  struct clad_Var_ result;
  result.type      = BADVAR_FPTR;
  result.value.fptr= value;
  return result;
}

void * clad_var_ptr(clad_Var self) {
  if (self.type != BADVAR_PTR) return NULL;
  return self.value.ptr;
}

clad_Function * clad_var_fptr(clad_Var self) {
  if (self.type != BADVAR_FPTR) return NULL;
  return self.value.fptr;
}

char * clad_var_cstr(clad_Var self) {
  if (self.type != BADVAR_CSTR) return NULL;
  return self.value.cstr;
}

int clad_var_int(clad_Var self) {
  if (self.type != BADVAR_INT) return 0;
  return self.value.i;
}

double clad_var_double(clad_Var self) {
  if (self.type != BADVAR_DOUBLE) return 0.0;
  return self.value.d;
}


void clad_var_store(clad_Var * self, void * ptr) {
  switch(self->type) { 
    case BADVAR_PTR   : (*((void **)ptr))        = self->value.ptr;
    break;
    case BADVAR_FPTR  : (*((clad_Function **)ptr)) = self->value.fptr;
    break; 
    case BADVAR_CSTR  : (*((char**)ptr))         = self->value.cstr;
    break; 
    case BADVAR_INT   : (*((int*)ptr))           = self->value.i;
    break;
    case BADVAR_DOUBLE: (*((double*)ptr))        = self->value.d;
    break;
    default: 
    break;
  }
}

clad_Var * clad_var_load(clad_Var * self, int type, void * ptr) {
  self->type = type;
  switch(self->type) { 
    case BADVAR_PTR   : self->value.ptr  = ptr;
    break;
    case BADVAR_FPTR  : self->value.fptr = (clad_Function*) ptr;
    break; 
    case BADVAR_CSTR  : self->value.cstr = (char*) ptr;
    break; 
    case BADVAR_INT   : self->value.i    = (*((int *)ptr));
    break;
    case BADVAR_DOUBLE: self->value.d    = (*((double*)ptr));
    break;
    default:
    break;
  }
  return self;
}

clad_Var clad_var_make(int type, void * valptr) {
  clad_Var self;
  clad_var_load(&self, type, valptr);
  return self;
}


int clad_var_toarrayva(int argc, clad_Var argv[], char * fmt, va_list args) {
  int index;
  for (index = 0; index < argc; index ++) {
    clad_Var * var = argv + index;
    int type = (int) fmt[index];
    if (type == 0) return index;
    switch(type) { 
      case BADVAR_PTR : 
        argv[index] = clad_var_makeptr(va_arg(args, void *)); 
      break;
      case BADVAR_FPTR  : 
        argv[index] = clad_var_makefptr(va_arg(args, clad_Function *)); 
      break;
      case BADVAR_CSTR  : 
        argv[index] = clad_var_makecstr(va_arg(args, char *)); 
      break;
      case BADVAR_INT   : 
        argv[index] = clad_var_makeint(va_arg(args, int)); 
      break; 
      case BADVAR_DOUBLE: 
        argv[index] = clad_var_makedouble(va_arg(args, double)); 
      break;
      default: 
      break;
    }
  }
  return index;
}

int clad_var_toarraylen(int argc, clad_Var argv[], char * fmt, ...) {
  va_list args;
  int result;
  va_start(args, fmt);
  result = clad_var_toarrayva(argc, argv, fmt, args);
  va_end(args);
  return result;
}

int clad_var_toarray(clad_Var argv[], char * fmt, ...) {
  va_list args;
  int argc; 
  int result;
  argc = strlen(fmt);
  va_start(args, fmt);
  result = clad_var_toarrayva(argc, argv, fmt, args);
  va_end(args);
  return result;
}


int clad_var_fromarrayva(clad_Var argv[], int argc, va_list args) {
  int index;
  for (index = 0; index < argc; index ++) {
    clad_Var * var = argv + index;
    switch(var->type) { 
      case BADVAR_PTR : 
        (*va_arg(args, void **)) = clad_var_ptr(argv[index]);
      break;
      case BADVAR_FPTR  : 
        (*va_arg(args, clad_Function **)) = clad_var_fptr(argv[index]);
      break;
      case BADVAR_CSTR  : 
        (*va_arg(args, char **)) = clad_var_cstr(argv[index]);
      break;
      case BADVAR_INT   : 
        (*va_arg(args, int *)) = clad_var_int(argv[index]);
      break; 
      case BADVAR_DOUBLE: 
        (*va_arg(args, double *)) = clad_var_double(argv[index]);
      break;
      default: 
      break;
    }
  }
  return index;
}

int clad_var_fromarray(clad_Var argv[], int argc, ...) {
  va_list args;
  int result;
  va_start(args, argc);
  result = clad_var_fromarrayva(argv, argc, args);
  va_end(args);
  return result;
}

/** This may not be very useful since it's hard to define. */
struct clad_VarList_ {
  struct clad_Var_ var;
  struct clad_ListNode_    list;
};

struct clad_VarList_ *
clad_varlist_init(struct clad_VarList_ * self, struct clad_Var_ var) {
  self->var = var;
  clad_listnode_init(&self->list);
  return self;
}  

clad_VarList *
clad_varlist_initva(clad_VarList * self, char * format, va_list args) {
  if((!self) || (!format))  { return NULL; } 
  for( ; (*format) ; format++) {
    
    
  }
  return self;
}

clad_VarList *
clad_varlist_initf(clad_VarList * self, char * format, ...) {
  clad_VarList * result;
  va_list args;
  va_start(args, format);
  result = clad_varlist_initva(self, format, args);
  va_end(args);
  return result;  
}

/*
 
This even works on gcc!

struct try_structfunc2_ { int value; int error ;} try_structfunc(int x, int y) {
  struct try_structfunc2_ result = { 1, 1};
  return result;
}
*/


/* Generic array handling that use no structs itself. */

/* New generic array. */
void * clad_gar_new(size_t nmemb, size_t size) {
  return calloc(nmemb, size);
}

/* Resizes the array. Returns NULL on failiure (it leaves arr untouched then)
 * On success arr is overwritten with the new reallocated pointer and 
 * non-null is returned. 
 */
void * clad_gar_resize(void ** arr, size_t  * nmemb, size_t size, int delta) {
  void * res;
  void * old;
  size_t old_nmemb;
  size_t res_nmemb;
  size_t copy_nmemb;
  
  if (!arr)   return NULL;
  if (!nmemb)   return NULL;
  
  old           = (*arr);
  old_nmemb     = (*nmemb);
  if(!(old)) return NULL;
  res_nmemb     = (size_t)((int)old_nmemb + delta);  
  if(res_nmemb < 1) return NULL;  
  res           = realloc(old, res_nmemb * size);
  (*arr)        = res;    
  (*nmemb)      = res_nmemb;
  return res;
}

/* Gets a pointer to an element of the generic array. Returns NULL on range error 
 * or if arr is null. */
void * clad_gar_get(void * arr, size_t nmemb, size_t size, size_t index) {
  char * ptr = arr; /* char * pointer avoids strict aliasing. */
  if(!arr) return NULL;
  if (index >= nmemb) return NULL;
  return ptr + (index * size);
}

/* Stores data in the generic array arr using memmove. */
void * clad_gar_put(void * arr, size_t nmemb, size_t size, size_t index, void * data) 
{
  char * ptr = arr; /* char * pointer avoids strict aliasing. */
  if(!arr) return NULL;
  if (index >= nmemb) return NULL;
  memmove(ptr + (index * size), data, size);
  return ptr + (index * size);
}

/* Just a wrapper for free(). Retruns NULL  */
void * clad_gar_free(void * arr) {
  free(arr);
  return NULL;
}


/* clad_par is for generic arrays of void pointers */

void * clad_par_new(size_t nmemb) {
  return clad_gar_new(nmemb, sizeof(void*));
}

void * clad_par_resize(void ** arr, size_t * nmemb, int delta) {
  return clad_gar_resize(arr, nmemb, sizeof(void*), delta);
}

void * clad_par_get(void * arr, size_t nmemb, size_t index) {
  return clad_gar_get(arr, nmemb, sizeof(void*), index);
}

void * clad_par_put(void * arr, size_t nmemb, size_t index, void * data) {
  return clad_gar_put(arr, nmemb, sizeof(void*), index, data);  
}

void * clad_par_free(void * arr) {
  return clad_gar_free(arr);
}






















