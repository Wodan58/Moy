/*
    module  : app3.c
    version : 1.6
    date    : 03/15/21
*/
#ifndef APP3_C
#define APP3_C

#ifdef UNARY3_X
#undef UNARY3_X
#undef UNARY3_C
#endif

#include "unary3.c"

/**
app3  :  X1 X2 X3 [P]  ->  R1 R2 R3
Obsolescent.  == unary3
*/
PRIVATE void do_app3(pEnv env)
{
    do_unary3(env);
}
/* app3.c */
#endif
