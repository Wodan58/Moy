/*
    module  : treerec.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef TREEREC_C
#define TREEREC_C

/**
OK 2900  treerec  :  DDDU	T [O] [C]  ->  ...
T is a tree. If T is a leaf, executes O. Else executes [[[O] C] treerec] C.
*/
void treerec_(pEnv env)
{
    PARM(3, WHILE);
    cons_(env);
    _treerec_(env);
}
#endif
