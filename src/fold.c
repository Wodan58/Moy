/*
    module  : fold.c
    version : 1.3
    date    : 09/11/23
*/
#ifndef FOLD_C
#define FOLD_C

/**
OK 2780  fold  :  DDDA	A V0 [P]  ->  V
Starting with value V0, sequentially pushes members of aggregate A
and combines with binary operator P to produce value V.
*/
void fold_(pEnv env)
{
#ifndef COMPILER
    PARM(3, DIP);
    swapd_(env);
    step_(env);
#endif
}
#endif
