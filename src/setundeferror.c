/*
    module  : setundeferror.c
    version : 1.7
    date    : 02/01/24
*/
#ifndef SETUNDEFERROR_C
#define SETUNDEFERROR_C

/**
OK 2990  setundeferror  :  D	I  ->
[IMPURE] Sets flag that controls behavior of undefined functions
(0 = no error, 1 = error).
*/
void setundeferror_(pEnv env)
{
    Node node;

    PARM(1, PREDSUCC);
    env->stck = pvec_pop(env->stck, &node);
    if (!env->ignore && !env->undeferror_set)
	env->undeferror = node.u.num;
}
#endif
