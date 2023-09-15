/*
    module  : argc.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef ARGC_C
#define ARGC_C

/**
OK 3050  argc  :  A	->  I
Pushes the number of command line arguments. This is quivalent to 'argv size'.
*/
void argc_(pEnv env)
{
    Node node;

    node.u.num = env->g_argc;
    node.op = INTEGER_;
    lst_push(env->stck, node);
}
#endif
