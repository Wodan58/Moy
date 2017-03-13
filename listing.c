/*
    module  : listing.c
    version : 1.1
    date    : 03/12/17
*/
#include <stdio.h>
#include <stdlib.h>
#include "joy.h"
#include "symbol.h"

#define MAXLEV		30

typedef struct list_t {
    void *ptr;
    unsigned num;
    struct list_t *next;
} list_t;

static list_t *root[MAXLEV];
static unsigned scope, count;

void NewScope(void)
{
    if (++scope == MAXLEV) {
	fprintf(stderr, "out of scope\n");
	exit(1);
    }
}

void OldScope(void)
{
    root[scope] = 0;
    if (scope)
	scope--;
}

unsigned Listed(void *ptr, int *found)
{
    int i;
    list_t *cur;

    *found = 0;
    for (i = scope; i >= 0; i--)
	for (cur = root[i]; cur; cur = cur->next)
	    if (cur->ptr == ptr) {
		*found = 1;
		return cur->num;
	    }
    cur = GC_malloc(sizeof(list_t));
    cur->ptr = ptr;
    cur->num = ++count;
    cur->next = root[scope];
    root[scope] = cur;
    return count;
}

void DeList(void)
{
    while (scope)
	root[scope--] = 0;
    root[scope = 0] = 0;
}
