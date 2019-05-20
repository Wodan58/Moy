/*
    module  : node.h
    version : 1.7
    date    : 05/18/19
*/
#ifdef _MSC_VER
extern Node *stk;

#define __func__	__FUNCTION__
#pragma warning( disable : 4244 4305 4996 )
#else
register Node *stk asm("bl");
#endif

Node *newnode(Operator op, void *u, Node *next);
Node *dblnode(double dbl, Node *next);
Node *reverse(Node *cur);
Node *stk2lst(void);
void lst2stk(Node *cur);

double Compare(Node *first, Node *second, int *error);
