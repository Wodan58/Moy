/*
    module  : node.h
    version : 1.10
    date    : 03/28/20
*/
#ifdef _MSC_VER
extern Node *stk;

#define __func__	__FUNCTION__
#pragma warning( disable : 4244 4305 4996 )
#else
register Node *stk asm("bl");
#endif

void freemem(void);
Node *newnode(Operator op, void *u, Node *next);
Node *dblnode(double dbl, Node *next);
Node *reverse(Node *cur);
Node *stk2lst(void);
void lst2stk(Node *cur);
