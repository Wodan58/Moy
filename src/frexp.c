/*
    module  : frexp.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef FREXP_C
#define FREXP_C

/**
frexp  :  F  ->  G I
G is the mantissa and I is the exponent of F.
Unless F = 0, 0.5 <= abs(G) < 1.0.
*/
PRIVATE void do_frexp(pEnv env)
{
    int exp;

    ONEPARAM("frexp");
    FLOAT("frexp");
    UNARY(FLOAT_NEWNODE, frexp(FLOATVAL, &exp));
    PUSH_NUM(INTEGER_, exp);
}
#endif
