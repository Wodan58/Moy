/*
    module  : app1.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef APP1_C
#define APP1_C

/**
Q1  OK  2440  app1  :  DDA  X [P]  ->  R
Obsolescent.  Executes P, pushes result R on stack.
*/
void app1_(pEnv env)
{
    Node node;

    PARM(2, DIP);
    env->stck = pvec_pop(env->stck, &node);
    prog(env, node.u.lis);
}
#endif
