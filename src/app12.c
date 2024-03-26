/*
    module  : app12.c
    version : 1.7
    date    : 03/21/24
*/
#ifndef APP12_C
#define APP12_C

/**
Q1  OK  2460  app12  :  DDDDAA  X Y1 Y2 [P]  ->  R1 R2
Executes P twice, with Y1 and Y2, returns R1 and R2.
*/
void app12_(pEnv env)
{
    /*	X  Y  Z  [P]  app12	*/
    PARM(4, DIP);
    code(env, pop_);
    code(env, rolldown_);
    unary2_(env);
}
#endif
