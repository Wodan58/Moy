/*
    module  : node.c
    version : 1.13
    date    : 06/15/22
*/
#include "runtime.h"

Node *newnode(Operator op, YYSTYPE u, Node *next)
{
    Node *node;

    node = GC_malloc(sizeof(Node));
    node->u = u;
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
