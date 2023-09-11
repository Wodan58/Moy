/*
    module  : app4.c
    version : 1.3
    date    : 09/11/23
*/
#ifndef APP4_C
#define APP4_C

/**
OK 2550  app4  :  DDDDDAAAA	X1 X2 X3 X4 [P]  ->  R1 R2 R3 R4
Obsolescent.  == unary4
*/
void app4_(pEnv env)
{
#ifndef COMPILER
    unary4_(env);
    /* filler */
#endif
}
#endif
