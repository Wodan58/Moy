/*
    module  : log.c
    version : 1.6
    date    : 10/02/23
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
    env->stck = pvec_pop(env->stck, &node);
    node.u.dbl = log(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    env->stck = pvec_add(env->stck, node);
}
#endif
