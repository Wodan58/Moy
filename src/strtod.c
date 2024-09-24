/*
    module  : strtod.c
    version : 1.8
    date    : 09/17/24
*/
#ifndef STRTOD_C
#define STRTOD_C

/**
Q0  OK  1750  strtod  :  DA  S  ->  R
String S is converted to the float R.
*/
void strtod_(pEnv env)
{
    Node node;

    PARM(1, STRTOD);
    node = vec_pop(env->stck);
    node.u.dbl = strtod(node.u.str, 0);
    node.op = FLOAT_;
    vec_push(env->stck, node);
}
#endif
