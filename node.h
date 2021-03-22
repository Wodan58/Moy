/*
    module  : node.h
    version : 1.10
    date    : 03/15/21
*/
Node *newnode(Operator op, YYSTYPE u, Node *next);
Node *dblnode(double dbl, Node *next);
Node *reverse(Node *cur);
Node *stk2lst(pEnv env);
void lst2stk(pEnv env, Node *cur);
