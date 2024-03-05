/*
    module  : argc.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef ARGC_C
#define ARGC_C

/**
Q0  OK  3050  argc  :  A  ->  I
Pushes the number of command line arguments. This is quivalent to 'argv size'.
*/
void argc_(pEnv env)
{
    Node node;

    node.u.num = env->g_argc;
    node.op = INTEGER_;
    env->stck = pvec_add(env->stck, node);
}
#endif
