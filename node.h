/*
    module  : node.h
    version : 1.2
    date    : 09/14/17
*/
#define MEMORYMAX	300

#ifdef _MSC_VER
extern Node *stk;

#define __func__	__FUNCTION__
#pragma warning( disable : 4244 4305 )
#else
register Node *stk asm("bl");
#endif

extern unsigned inside_condition;
extern Node memory[], condition[], *condition_stack[], *cond_ptr;

Node *newnode(Operator op, void *u, Node *next);
Node *dblnode(double dbl, Node *next);
Node *heapnode(Operator op, void *u, Node *next);
Node *reverse(Node *cur);
