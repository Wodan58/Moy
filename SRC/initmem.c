/*
    module  : initmem.c
    version : 1.10
    date    : 09/14/17
*/
#include "runtime.h"

static Node *oldstk;

/*
    Make a backup of the stack
*/
static Node *backup(void)
{
    Node *root = 0, *cur;

    for (cur = stk; cur != memory; cur = cur->next)
	root = heapnode(cur->op, cur->u.ptr, root);
    return root;
}

/*
    Restore an old copy of the stack
*/
static void restore(Node *cur)
{
    for (stk = memory; cur; cur = cur->next)
	DUPLICATE(cur);
}

void initmem(void)
{
    static unsigned char init;

    if (!init) {
	init = 1;
	stk = &memory[MEMORYMAX];
	while (--stk > memory)
	    stk->next = stk - 1;
	stk->next = memory;
    }
    stk = memory;
}

void savemem(void)
{
    oldstk = backup();
}

void backmem(void)
{
    restore(oldstk);
}
