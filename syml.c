/*
    module  : syml.c
    date    : 1.3
    version : 07/14/23
*/
#include <stdio.h>
#include <string.h>
#include <gc.h>
#include "globals.h"

/* initialize vector header and set the array as not owned by the head */
void sym_init_again(SymList **v)
{
    *v = GC_malloc(sizeof(SymList));
    (*v)->m = (*v)->n = 0;
    (*v)->a = 0;
}

/* sym_push assumes that v has been initialized to 0 before its called */
void sym_push(SymList *v, Entry x)
{
    void *ptr;
    unsigned m;

    if (v->n == v->m) {
        m = v->m ? v->m << 1 : 1;
        ptr = GC_malloc(m * sizeof(Entry));
        memcpy(ptr, v->a, v->m * sizeof(Entry));
        v->a = ptr;
        v->m = m;
    }
    v->a[v->n++] = x;
}

int sym_size(SymList *v)
{
    return v ? v->n : 0;
}

Entry sym_at(SymList *v, int i)
{
    return v->a[i];
}

Entry *sym_lvalue(SymList *v, int i)
{
    return &v->a[i];
}

int sym_max(SymList *v)
{
    return v->m;
}
