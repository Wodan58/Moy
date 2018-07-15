/*
    module  : app2.c
    version : 1.4
    date    : 07/15/18
*/
#ifndef APP2_X
#define APP2_C

#ifndef UNARY2_C
#undef UNARY2_X
#include "unary2.c"
#define UNARY2_X
#endif

/**
app2  :  X1 X2 [P]  ->  R1 R2
Obsolescent.  ==  unary2
*/
PRIVATE void do_app2(void)
{
    do_unary2();
}
/* app2.c */
#endif
