/*
    module  : treerec.c
    version : 1.5
    date    : 10/02/23
*/
#ifndef TREEREC_C
#define TREEREC_C

/**
OK 2880  treerec  :  DDDU	T [O] [C]  ->  ...
T is a tree. If T is a leaf, executes O. Else executes [[[O] C] treerec] C.
*/
void treerec_(pEnv env)
{
    PARM(3, WHILE);
    cons_(env);
    ytreerec_(env);
}
#endif
