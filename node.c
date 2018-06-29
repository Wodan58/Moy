/*
    module  : node.c
    version : 1.3
    date    : 06/29/18
*/
#include "runtime.h"

#define MAXCOND		100

#ifdef _MSC_VER
Node *stk;
#endif

#if 0
unsigned inside_condition;

Node condition[MAXCOND], *cond_ptr = condition,
    *condition_stack[MAXCOND];
#endif

Node memory[MEMORYMAX];

static Node *getnode(void)
{
    Node *node;

#if 0
    if (inside_condition)
	if (cond_ptr < &condition[MAXCOND])
	    return cond_ptr++;
#endif
    if ((node = GC_malloc(sizeof(Node))) == 0)
	execerror("memory", "allocator");
    return node;
}

Node *newnode(Operator op, void *u, Node *next)
{
    Node *node;

    node = getnode();
    node->u.ptr = u;
    node->op = op;
    node->next = next;
    return node;
}

Node *dblnode(double dbl, Node *next)
{
    Node *node;

    node = getnode();
    node->u.dbl = dbl;
    node->op = FLOAT_;
    node->next = next;
    return node;
}

Node *heapnode(Operator op, void *u, Node *next)
{
    Node *node;

    if ((node = GC_malloc(sizeof(Node))) == 0)
	execerror("memory", "allocator");
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

    for (cur = &root; stk != memory; stk = stk->next) {
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
