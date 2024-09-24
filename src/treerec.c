/*
    module  : treerec.c
    version : 1.10
    date    : 09/17/24
*/
#ifndef TREEREC_C
#define TREEREC_C

/**
Q2  OK  2880  treerec  :  DDDA  T [O] [C]  ->  ...
T is a tree. If T is a leaf, executes O. Else executes [[[O] C] treerec] C.
*/
void treerec_(pEnv env)
{
    PARM(3, WHILE);
    cons_(env);
    treerecaux_(env);
}
#endif
