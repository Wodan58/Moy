/*
    module  : false.c
    version : 1.9
    date    : 09/17/24
*/
#ifndef FALSE_C
#define FALSE_C

/**
Q0  IMMEDIATE  1000  false  :  A  ->  false
Pushes the value false.
*/
void false_(pEnv env)
{
    Node node;

    node.u.num = 0;
    node.op = BOOLEAN_;
    vec_push(env->stck, node);
}
#endif
