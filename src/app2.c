/*
    module  : app2.c
    version : 1.3
    date    : 09/11/23
*/
#ifndef APP2_C
#define APP2_C

/**
OK 2530  app2  :  DDDAA	X1 X2 [P]  ->  R1 R2
Obsolescent.  ==  unary2
*/
void app2_(pEnv env)
{
#ifndef COMPILER
    unary2_(env);
    /* filler */
#endif
}
#endif
