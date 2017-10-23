/*
    module  : backup.c
    version : 1.2
    date    : 03/18/17
*/
#include "runtime.h"

/*
    Make a backup of the stack
*/
PRIVATE Node *backup(void)
{
    Node *root = 0, *cur;

    for (cur = stk; cur != memory; cur = cur->next)
	root = heapnode(cur->op, cur->u.ptr, root);
    return root;
}

/*
    Restore an old copy of the stack
*/
PRIVATE void restore(Node *cur)
{
    for (stk = memory; cur; cur = cur->next)
	DUPLICATE(cur);
}
