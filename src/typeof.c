/*
    module  : %M%
    version : %I%
    date    : %G%
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
