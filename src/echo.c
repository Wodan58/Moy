/*
    module  : echo.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef ECHO_C
#define ECHO_C

/**
OK 1120  echo  :  A	->  I
Pushes value of echo flag, I = 0..3.
*/
void echo_(pEnv env)
{
#ifndef COMPILER
    Node node;

    node.u.num = env->echoflag;
    node.op = INTEGER_;
    lst_push(env->stck, node);
#endif
}
#endif
