/*
    module  : false.c
    version : 1.2
    date    : 08/23/23
*/
#ifndef FALSE_C
#define FALSE_C

/**
IMMEDIATE 1000  false  :  A	->  false
Pushes the value false.
*/
void false_(pEnv env)
{
    Node node;

    node.u.num = 0;
    node.op = BOOLEAN_;
    lst_push(env->stck, node);
}
#endif
