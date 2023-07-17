/*
    module  : x.c
    version : 1.2
    date    : 07/17/23
*/
#ifndef X_C
#define X_C

/**
OK 2440  x  :  P	[P] x  ->  ...
Executes P without popping [P]. So, [P] x  ==  [P] P.
*/
void x_(pEnv env)
{
    Node node;

    PARM(1, DIP);
    node = vec_back(env->stck);
    prog(env, node.u.lis);
}
#endif
