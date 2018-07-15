/*
    module  : app4.c
    version : 1.4
    date    : 07/15/18
*/
#ifndef APP4_X
#define APP4_C

#ifndef UNARY4_C
#undef UNARY4_X
#include "unary4.c"
#define UNARY4_X
#endif

/**
app4  :  X1 X2 X3 X4 [P]  ->  R1 R2 R3 R4
Obsolescent.  == unary4
*/
PRIVATE void do_app4(void)
{
    do_unary4();
}
/* app4.c */
#endif
