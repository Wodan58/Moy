/*
    module  : app3.c
    version : 1.3
    date    : 09/11/23
*/
#ifndef APP3_C
#define APP3_C

/**
OK 2540  app3  :  DDDDAAA	X1 X2 X3 [P]  ->  R1 R2 R3
Obsolescent.  == unary3
*/
void app3_(pEnv env)
{
#ifndef COMPILER
    unary3_(env);
    /* filler */
#endif
}
#endif
