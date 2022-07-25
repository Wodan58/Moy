/*
    module  : typeof.c
    version : 1.1
    date    : 07/13/22
*/
#ifndef TYPEOF_C
#define TYPEOF_C

/**
typeof  :  X  ->  I
Replace X by its type.
*/
void do_typeof(pEnv env)
{
    ONEPARAM("typeof");
    UNARY(INTEGER_NEWNODE, env->stk->op);
}
#endif
