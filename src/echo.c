/*
    module  : echo.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef ECHO_C
#define ECHO_C

/**
Q0  OK  1120  echo  :  A  ->  I
Pushes value of echo flag, I = 0..3.
*/
void echo_(pEnv env)
{
    Node node;

    node.u.num = env->echoflag;
    node.op = INTEGER_;
    env->stck = pvec_add(env->stck, node);
}
#endif
