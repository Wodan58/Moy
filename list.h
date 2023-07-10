/*
    module  : list.h
    date    : 1.1
    version : 07/10/23
*/
struct NodeList {
    unsigned long m : 30, /* capacity */
                  n : 30, /* valid items */
                  o :  1, /* ownership */
                  t :  2, /* arity */
                  u :  1; /* unused */
    YYSTYPE *a;           /* union */
    Operator *b;          /* datatype */
};

/* arity tells: saving and restoring stack in a condition is necessary */
enum arity_t {
    ARITY_UNKNOWN, /* not yet calculated */
    ARITY_NOT_OK,
    ARITY_OK
};

#define vec_init(v)	vec_init_again(&(v))

/* initialize vector header and set the array as not owned by the head */
void vec_init_again(NodeList **v);

/* vec_push assumes that v has been initialized to 0 before its called */
void vec_push(NodeList *v, Node x);

/* vec_copy assumes that v does not exist yet, and needs to be created */
void vec_copy(NodeList *v, NodeList *w);

/* vec_shallow_copy makes a copy without taking ownership of the array */
void vec_shallow_copy(NodeList *v, NodeList *w);

/* vec_shallow_copy_take_ownership makes a copy while taking ownership */
void vec_shallow_copy_take_ownership(NodeList *v, NodeList *w);

Node vec_at(NodeList *v, int i);

void vec_assign(NodeList *v, int i, Node x);

Node vec_pop(NodeList *v);

Node vec_back(NodeList *v);

int vec_size(NodeList *v);

void vec_resize(NodeList *v, int s);

int vec_max(NodeList *v);

int vec_getarity(NodeList *v);

void vec_setarity(NodeList *v, int s);

/* vec_reverse assumes that an extra element has been added as scratch */
void vec_reverse(NodeList *v);
