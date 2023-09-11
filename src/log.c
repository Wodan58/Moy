/*
    module  : log.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef LOG_C
#define LOG_C

/**
OK 1600  log  :  DA	F  ->  G
G is the natural logarithm of F.
*/
void log_(pEnv env)
{
#ifndef COMPILER
    Node node;

    PARM(1, UFLOAT);
    node = lst_pop(env->stck);
    node.u.dbl = log(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    lst_push(env->stck, node);
#endif
}
#endif
