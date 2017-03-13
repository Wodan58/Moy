/*
    module  : node.h
    version : 1.1
    date    : 03/12/17
*/
#define MEMORYMAX	300

#ifdef _MSC_VER
extern Node *stk;

#define __func__	__FUNCTION__
#else
register Node *stk asm("bl");
#endif

extern unsigned inside_condition;
extern Node memory[], condition[], *condition_stack[], *cond_ptr;

Node *newnode(Operator op, void *u, Node *next);
Node *dblnode(double dbl, Node *next);
Node *heapnode(Operator op, void *u, Node *next);
Node *reverse(Node *cur);
