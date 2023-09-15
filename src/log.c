/*
    module  : log.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef LOG_C
#define LOG_C

/**
OK 1600  log  :  DA	F  ->  G
G is the natural logarithm of F.
*/
void log_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    node = lst_pop(env->stck);
    node.u.dbl = log(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    lst_push(env->stck, node);
}
#endif
