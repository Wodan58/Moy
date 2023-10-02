/*
    module  : strtod.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef STRTOD_C
#define STRTOD_C

/**
OK 1750  strtod  :  DA	S  ->  R
String S is converted to the float R.
*/
void strtod_(pEnv env)
{
    Node node;

    PARM(1, STRTOD);
    env->stck = pvec_pop(env->stck, &node);
    node.u.dbl = strtod(node.u.str, 0);
    node.op = FLOAT_;
    env->stck = pvec_add(env->stck, node);
}
#endif
