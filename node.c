/*
    module  : node.c
    version : 1.11
    date    : 03/15/21
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

Node *dblnode(double dbl, Node *next)
{
    Node *node;

    node = GC_malloc(sizeof(Node));
    node->u.dbl = dbl;
    node->op = FLOAT_;
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
 * Copy the stack to a list; do not empty the stack.
 */
Node *stk2lst(pEnv env)
{
    Node *root = 0, **cur, *mem;

    for (cur = &root, mem = env->stk; mem; mem = mem->next) {
	*cur = newnode(mem->op, mem->u, 0);
	cur = &(*cur)->next;
    }
    return root;
}

/*
 * Copy a list to the stack.
 */
void lst2stk(pEnv env, Node *cur)
{
    if (cur) {
	lst2stk(env, cur->next);
	DUPLICATE(cur);
    }
}
