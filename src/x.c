/*
    module  : x.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef X_C
#define X_C

/**
OK 2440  x  :  U	[P] x  ->  ...
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
