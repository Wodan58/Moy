/*
    module  : treerec.c
    version : 1.8
    date    : 01/24/24
*/
#ifndef TREEREC_C
#define TREEREC_C

/**
OK 2880  treerec  :  DDDA	T [O] [C]  ->  ...
T is a tree. If T is a leaf, executes O. Else executes [[[O] C] treerec] C.
*/
void treerec_(pEnv env)
{
    PARM(3, WHILE);
    cons_(env);
    treerecaux_(env);
}
#endif
