/*
    module  : x.c
    version : 1.8
    date    : 03/05/24
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
    node = pvec_lst(env->stck);
    prog(env, node.u.lis);
}
#endif
