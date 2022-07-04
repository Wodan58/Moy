/*
    module  : node.h
    version : 1.11
    date    : 06/16/22
*/
Node *newnode(Operator op, YYSTYPE u, Node *next);
Node *reverse(Node *cur);

/* src/compare.h */
int Compare(pEnv env, Node *first, Node *second);
