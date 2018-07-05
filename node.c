/*
    module  : node.c
    version : 1.5
    date    : 07/05/18
*/
#include "runtime.h"

#ifdef _MSC_VER
Node *stk;
#endif

Node *newnode(Operator op, void *u, Node *next)
{
    Node *node;

    node = get1node();
    node->u.ptr = u;
    node->op = op;
    node->next = next;
    return node;
}

Node *dblnode(double dbl, Node *next)
{
    Node *node;

    node = get1node();
    node->u.dbl = dbl;
    node->op = FLOAT_;
    node->next = next;
    return node;
}

Node *heapnode(Operator op, void *u, Node *next)
{
    Node *node;

    node = get2node();
    node->u.ptr = u;
    node->op = op;
    node->next = next;
    return node;
}

Node *reverse(Node *cur)
{
    Node *old = 0, *prev;

    while (cur) {
	prev = cur;
	cur = cur->next;
	prev->next = old;
	old = prev;
    }
    return old;
}

/*
    Copy the stack to a list
*/
Node *stk2lst(void)
{
    Node *root = 0, **cur;

    for (cur = &root; stk; stk = stk->next) {
	*cur = heapnode(stk->op, stk->u.ptr, 0);
	cur = &(*cur)->next;
    }
    return root;
}

/*
    Replace the stack by a list
*/
void lst2stk(Node *cur)
{
    if (cur) {
	lst2stk(cur->next);
	DUPLICATE(cur);
    }
}
