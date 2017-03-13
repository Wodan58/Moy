/*
    module  : backup.c
    version : 1.1
    date    : 03/12/17
*/
#include "runtime.h"

/*
    Make a backup of the stack (can be done with memcpy)
*/
PRIVATE Node *backup(void)
{
    Node *root = 0, *cur;

    for (cur = stk; cur != memory; cur = cur->next)
	root = heapnode(cur->op, cur->u.ptr, root);
    return root;
}

/*
    Restore an old copy of the stack (also memcpy)
*/
PRIVATE void restore(Node *cur)
{
    for (stk = memory; cur; cur = cur->next)
	DUPLICATE(cur);
}
