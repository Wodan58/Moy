/*
    module  : x.c
    version : 1.9
    date    : 09/17/24
*/
#ifndef X_C
#define X_C

/**
Q1  OK  2420  x  :  P  [P] x  ->  ...
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
