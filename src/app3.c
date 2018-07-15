/*
    module  : app3.c
    version : 1.4
    date    : 07/15/18
*/
#ifndef APP3_X
#define APP3_C

#ifndef UNARY3_C
#undef UNARY3_X
#include "unary3.c"
#define UNARY3_X
#endif

/**
app3  :  X1 X2 X3 [P]  ->  R1 R2 R3
Obsolescent.  == unary3
*/
PRIVATE void do_app3(void)
{
    do_unary3();
}
/* app3.c */
#endif
