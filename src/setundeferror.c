/*
    module  : setundeferror.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef SETUNDEFERROR_C
#define SETUNDEFERROR_C

/**
OK 2990  setundeferror  :  D	I  ->
Sets flag that controls behavior of undefined functions
(0 = no error, 1 = error).
*/
void setundeferror_(pEnv env)
{
#ifndef COMPILER
    Node node;

    PARM(1, PREDSUCC);
    node = lst_pop(env->stck);
    env->undeferror = node.u.num;
#endif
}
#endif
