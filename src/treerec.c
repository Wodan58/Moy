/*
    module  : treerec.c
    version : 1.3
    date    : 09/11/23
*/
#ifndef TREEREC_C
#define TREEREC_C

/**
OK 2880  treerec  :  DDDU	T [O] [C]  ->  ...
T is a tree. If T is a leaf, executes O. Else executes [[[O] C] treerec] C.
*/
void treerec_(pEnv env)
{
#ifndef COMPILER
    PARM(3, WHILE);
    cons_(env);
    ztreerec_(env);
#endif
}
#endif
