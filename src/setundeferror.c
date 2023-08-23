/*
    module  : setundeferror.c
    version : 1.2
    date    : 08/23/23
*/
#ifndef SETUNDEFERROR_C
#define SETUNDEFERROR_C

/**
OK 3010  setundeferror  :  D	I  ->
Sets flag that controls behavior of undefined functions
(0 = no error, 1 = error).
*/
void setundeferror_(pEnv env)
{
    Node node;

    PARM(1, PREDSUCC);
    node = lst_pop(env->stck);
    env->undeferror = node.u.num;
}
#endif
