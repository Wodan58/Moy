/*
    module  : fold.c
    version : 1.7
    date    : 09/17/24
*/
#ifndef FOLD_C
#define FOLD_C

/**
Q1  OK  2780  fold  :  DDDA  A V0 [P]  ->  V
Starting with value V0, sequentially pushes members of aggregate A
and combines with binary operator P to produce value V.
*/
void fold_(pEnv env)
{
    PARM(3, DIP);
    swapd_(env);
    step_(env);
}
#endif
