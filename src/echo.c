/*
    module  : echo.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef ECHO_C
#define ECHO_C

/**
OK 1120  echo  :  A	->  I
Pushes value of echo flag, I = 0..3.
*/
void echo_(pEnv env)
{
    Node node;

    node.u.num = env->echoflag;
    node.op = INTEGER_;
    lst_push(env->stck, node);
}
#endif
