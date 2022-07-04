/*
    module  : strtod.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef STRTOD_C
#define STRTOD_C

/**
strtod  :  S  ->  R
String S is converted to the float R.
*/
PRIVATE void do_strtod(pEnv env)
{
    ONEPARAM("strtod");
    STRING("strtod");
    UNARY(FLOAT_NEWNODE, strtod(env->stk->u.str, 0));
}
#endif
