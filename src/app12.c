/*
    module  : app12.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef APP12_C
#define APP12_C

/**
OK 2480  app12  :  DDDDAA	X Y1 Y2 [P]  ->  R1 R2
Executes P twice, with Y1 and Y2, returns R1 and R2.
*/
PRIVATE void app12_(pEnv env)
{
    /*   X  Y  Z  [P]  app12  */
    PARM(4, DIP);
    code(env, pop_); /* delete X */
    code(env, rolldown_);
    unary2_(env);
}
#endif
