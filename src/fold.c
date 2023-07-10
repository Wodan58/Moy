/*
    module  : fold.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef FOLD_C
#define FOLD_C

/**
OK 2800  fold  :  DDDA	A V0 [P]  ->  V
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
