/*
    module  : app1.c
    version : 1.8
    date    : 09/17/24
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
    node = vec_pop(env->stck);
    prog(env, node.u.lis);
}
#endif
