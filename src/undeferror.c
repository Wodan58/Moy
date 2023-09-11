/*
    module  : undeferror.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef UNDEFERROR_C
#define UNDEFERROR_C

/**
OK 1100  undeferror  :  A	->  I
Pushes current value of undefined-is-error flag.
*/
void undeferror_(pEnv env)
{
#ifndef COMPILER
    Node node;

    node.u.num = env->undeferror;
    node.op = INTEGER_;
    lst_push(env->stck, node);
#endif
}
#endif
