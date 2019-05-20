/*
    module  : initmem.c
    version : 1.13
    date    : 05/18/19
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
	root = newnode(cur->op, cur->u.ptr, root);
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

void savemem(void)
{
    oldstk = backup();
}

void backmem(void)
{
    restore(oldstk);
}
