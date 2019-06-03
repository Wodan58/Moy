/*
    module  : node.c
    version : 1.8
    date    : 05/30/19
*/
#include "runtime.h"

#ifdef _MSC_VER
Node *stk;
#endif

static int memptr;
static Node memory[MEMORYMAX];

#ifdef REPORT
static double count_memory, count_heap, count_outside;

void report_memory()
{
    fprintf(stderr, "memory  = %.0f\n", count_memory);
    fprintf(stderr, "heap    = %.0f\n", count_heap);
    fprintf(stderr, "outside = %.0f\n", count_outside);
}
#endif

/*
 * getnode allocates nodes from a static array, unless definition is active and
 * as long as the array is not exhausted.
 */
Node *getnode(void)
{
#ifdef REPORT
    static int first;

    if (!first) {
	first = 1;
	atexit(report_memory);
    }
    count_memory++;
#endif
    if (!definition && memptr < MEMORYMAX)
	return &memory[memptr++];
#ifdef REPORT
    count_heap++;
    if (!definition)
	count_outside++;
#endif
    return ck_malloc(sizeof(Node));
}

/*
 * freemem releases the memory that was allocated outside definitions.
 */
void freemem(void)
{
#ifdef OK_TO_FREE_MEM
    memset(memory, 0, memptr * sizeof(Node));
    memptr = 0;
#endif
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
