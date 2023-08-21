/*
    module  : tokl.c
    date    : 1.1
    version : 08/21/23
*/
#include <stdio.h>
#include <string.h>
#include <gc.h>
#include "globals.h"

/* initialize vector header and set the array as not owned by the head */
void tok_init_again(TokList **v)
{
    *v = GC_malloc(sizeof(TokList));
    (*v)->m = (*v)->n = 0;
    (*v)->a = 0;
}

/* tok_push assumes that v has been initialized to 0 before its called */
void tok_push(TokList *v, Token x)
{
    void *ptr;
    unsigned m;

    if (v->n == v->m) {
        m = v->m ? v->m << 1 : 1;
        ptr = GC_malloc(m * sizeof(Token));
        memcpy(ptr, v->a, v->m * sizeof(Token));
        v->a = ptr;
        v->m = m;
    }
    v->a[v->n++] = x;
}

int tok_size(TokList *v)
{
    return v ? v->n : 0;
}

Token tok_pop(TokList *v)
{
    return v->a[--v->n];
}

void tok_setsize(TokList *v, int i)
{
    v->n = i;
}

void tok_reverse(TokList *v)
{
    int i, j, k = tok_size(v) - 1;

    for (i = 0, j = k - 1; i < j; i++, j--) {
	v->a[k] = v->a[i];
	v->a[i] = v->a[j];
	v->a[j] = v->a[k];
    }
    tok_setsize(v, k);
}
