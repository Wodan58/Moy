/*
    module  : setundeferror.c
    version : 1.6
    date    : 10/02/23
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
    Node node;

    PARM(1, PREDSUCC);
    env->stck = pvec_pop(env->stck, &node);
    env->undeferror = node.u.num;
}
#endif
