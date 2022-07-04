/*
    module  : app2.c
    version : 1.7
    date    : 06/20/22
*/
#ifndef APP2_C
#define APP2_C

#ifdef UNARY2_X
#undef UNARY2_X
#undef UNARY2_C
#endif

#include "unary2.c"

/**
app2  :  X1 X2 [P]  ->  R1 R2
Obsolescent.  ==  unary2
*/
PRIVATE void do_app2(pEnv env)
{
    do_unary2(env);
}
/* app2.c */
#endif
