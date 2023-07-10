/*
    module  : strtod.c
    version : 1.1
    date    : 07/10/23
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
    node = vec_pop(env->stck);
    node.u.dbl = strtod(node.u.str, 0);
    node.op = FLOAT_;
    vec_push(env->stck, node);
}
#endif
