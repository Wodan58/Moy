/*
    module  : node.c
    version : 1.1
    date    : 03/12/17
*/
#include <stdio.h>
#include <stdlib.h>
#include "joy.h"
#include "symbol.h"

#define MAXCOND		100

#ifdef _MSC_VER
Node *stk;
#endif

unsigned inside_condition;

Node condition[MAXCOND], *cond_ptr = condition,
    *condition_stack[MAXCOND];

Node memory[MEMORYMAX];

static Node *getnode(void)
{
    Node *node;

    if (inside_condition)
	if (cond_ptr < &condition[MAXCOND])
	    return cond_ptr++;
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
