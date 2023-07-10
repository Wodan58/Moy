/*
    module  : list.c
    date    : 1.1
    version : 07/10/23
*/
#include <stdio.h>
#include <string.h>
#include <gc.h>
#include "globals.h"

/* ownership determines whether the vector can have new elements added */
enum owner_t {
    NOT_OWNER,
    OWNER,
};

/* initialize vector header and set the array as not owned by the head */
void vec_init_again(NodeList **v)
{
    *v = GC_malloc(sizeof(NodeList));
    (*v)->t = ARITY_UNKNOWN;
    (*v)->m = (*v)->n = 0;
    (*v)->a = 0;
    (*v)->b = 0;
    (*v)->o = NOT_OWNER;
}

/* vec_push assumes that v has been initialized to 0 before its called */
void vec_push(NodeList *v, Node x)
{
    void *ptr;
    unsigned m;

    if (v->o == NOT_OWNER && v->n) {
        ptr = GC_malloc(v->n * sizeof(YYSTYPE));
        memcpy(ptr, v->a, v->n * sizeof(YYSTYPE));
        v->a = ptr;
        ptr = GC_malloc(v->n);
        memcpy(ptr, v->b, v->n);
        v->b = ptr;
        v->o = OWNER;
    }
    if (v->n == v->m) {
        m = v->m ? v->m << 1 : 1;
        ptr = GC_malloc(m * sizeof(YYSTYPE));
        memcpy(ptr, v->a, v->m * sizeof(YYSTYPE));
        v->a = ptr;
        ptr = GC_malloc(m);
        memcpy(ptr, v->b, v->m);
        v->b = ptr;
        v->m = m;
        v->o = OWNER;
    }
    v->a[v->n] = x.u;
    v->b[v->n++] = x.op;
}

/* vec_copy assumes that v exists and need not be created; array is ok */
void vec_copy(NodeList *v, NodeList *w)
{
    if ((v->n = vec_size(w)) != 0) { /* set new number of items */
        if (v->n > v->m) { /* new number exceeds maximum */
            v->a = GC_malloc(v->n * sizeof(YYSTYPE));
            v->b = GC_malloc(v->n);
            v->t = w->t;
            v->m = v->n;
            v->o = OWNER;
        }
        memcpy(v->a, w->a, v->n * sizeof(YYSTYPE));
        memcpy(v->b, w->b, v->n);
    }
}

/* vec_shallow_copy makes a copy without taking ownership of the array */
void vec_shallow_copy(NodeList *v, NodeList *w)
{
    v->m = w->m;
    v->n = w->n;
    v->t = w->t;
    v->a = w->a;
    v->b = w->b;
}

/* vec_shallow_copy_take_ownership makes a copy while taking ownership */
void vec_shallow_copy_take_ownership(NodeList *v, NodeList *w)
{
    if (w->o == OWNER) {
        vec_shallow_copy(v, w);
        v->o = OWNER;
        w->o = NOT_OWNER;
    } else
        vec_copy(v, w);
}

Node vec_at(NodeList *v, int i)
{
    Node node;

    node.u = v->a[i];
    node.op = v->b[i];
    return node;
}

void vec_assign(NodeList *v, int i, Node x)
{
    v->a[i] = x.u;
    v->b[i] = x.op;
}

Node vec_pop(NodeList *v)
{
    Node node;

    node.u = v->a[--v->n];
    node.op = v->b[v->n];
    return node;
}

Node vec_back(NodeList *v)
{
    Node node;

    node.u = v->a[v->n - 1];
    node.op = v->b[v->n - 1];
    return node;
}

int vec_size(NodeList *v)
{
    return v ? v->n : 0;
}

void vec_resize(NodeList *v, int s)
{
    v->n = s;
}

int vec_max(NodeList *v)
{
    return v->m;
}

int vec_getarity(NodeList *v)
{
    return v->t;
}

void vec_setarity(NodeList *v, int s)
{
    v->t = s;
}

/* vec_reverse assumes that an extra element has been added as scratch */
void vec_reverse(NodeList *v)
{
    int i, j, k = vec_size(v) - 1;

    for (i = 0, j = k - 1; i < j; i++, j--) {
        v->a[k] = v->a[i];
        v->b[k] = v->b[i];
        v->a[i] = v->a[j];
        v->b[i] = v->b[j];
        v->a[j] = v->a[k];
        v->b[j] = v->b[k];
    }
    vec_resize(v, k);
}
