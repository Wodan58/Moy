/*
    module  : modf.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef MODF_C
#define MODF_C

/**
modf  :  F  ->  G H
G is the fractional part and H is the integer part
(but expressed as a float) of F.
*/
PRIVATE void do_modf(pEnv env)
{
    double exp;

    ONEPARAM("modf");
    FLOAT("modf");
    NULLARY(FLOAT_NEWNODE, modf(FLOATVAL, &exp));
    PUSH_DBL(exp);
}
#endif
