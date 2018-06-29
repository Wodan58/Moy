/*
    module  : node.h
    version : 1.4
    date    : 06/29/18
*/
#define MEMORYMAX	300

#ifdef _MSC_VER
extern Node *stk;

#define __func__	__FUNCTION__
#pragma warning( disable : 4244 4305 )
#else
register Node *stk asm("bl");
#endif

extern Node memory[];

#if 0
extern unsigned inside_condition;
extern Node memory[], condition[], *condition_stack[], *cond_ptr;
#endif

Node *newnode(Operator op, void *u, Node *next);
Node *dblnode(double dbl, Node *next);
Node *heapnode(Operator op, void *u, Node *next);
Node *reverse(Node *cur);
Node *stk2lst(void);
void lst2stk(Node *cur);
double Compare(Node *first, Node *second, int *error);
