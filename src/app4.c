/*
    module  : app4.c
    version : 1.5
    date    : 03/28/20
*/
#ifndef APP4_C
#define APP4_C

#ifdef UNARY4_X
#undef UNARY4_X
#undef UNARY4_C
#endif

#include "unary4.c"

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
