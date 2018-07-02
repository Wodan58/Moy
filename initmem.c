/*
    module  : initmem.c
    version : 1.11
    date    : 07/02/18
*/
#include "runtime.h"

static Node *oldstk;

/*
    Make a backup of the stack
*/
static Node *backup(void)
{
    Node *root = 0, *cur;

    for (cur = stk; cur; cur = cur->next)
	root = heapnode(cur->op, cur->u.ptr, root);
    return root;
}

/*
    Restore an old copy of the stack
*/
static void restore(Node *cur)
{
    for (stk = 0; cur; cur = cur->next)
	DUPLICATE(cur);
}

void initmem(void)
{
    stk = 0;
}

void savemem(void)
{
    oldstk = backup();
}

void backmem(void)
{
    restore(oldstk);
}
