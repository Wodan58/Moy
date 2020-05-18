/*
    module  : node.c
    version : 1.10
    date    : 05/13/20
*/
#include "runtime.h"

#ifdef _MSC_VER
Node *stk;
#endif

static Node *getnode(void)
{
    return ck_malloc(sizeof(Node));
}

/*
 * freemem releases the memory that was allocated outside definitions.
 */
void freemem(void)
{
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
Node *stk2lst(void)
{
    Node *root = 0, **cur, *mem;

    for (cur = &root, mem = stk; mem; mem = mem->next) {
	*cur = newnode(mem->op, mem->u.ptr, 0);
	cur = &(*cur)->next;
    }
    return root;
}

/*
 * Copy a list to the stack.
 */
void lst2stk(Node *cur)
{
    if (cur) {
	lst2stk(cur->next);
	DUPLICATE(cur);
    }
}
