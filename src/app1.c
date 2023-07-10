/*
    module  : app1.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef APP1_C
#define APP1_C

/**
OK 2460  app1  :  DDA	X [P]  ->  R
Executes P, pushes result R on stack.
*/
void app1_(pEnv env)
{
    Node node;

    PARM(2, DIP);
    node = vec_pop(env->stck);
    prog(env, node.u.lis);
}
#endif
