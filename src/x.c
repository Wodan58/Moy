/*
    module  : x.c
    version : 1.6
    date    : 09/15/23
*/
#ifndef X_C
#define X_C

/**
OK 2420  x  :  P	[P] x  ->  ...
Executes P without popping [P]. So, [P] x  ==  [P] P.
*/
void x_(pEnv env)
{
    Node node;

    PARM(1, DIP);
    node = lst_back(env->stck);
    prog(env, node.u.lis);
}
#endif
