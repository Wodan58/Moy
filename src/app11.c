/*
    module  : app11.c
    version : 1.6
    date    : 03/05/24
*/
#ifndef APP11_C
#define APP11_C

/**
Q1  OK  2450  app11  :  DDDA  X Y [P]  ->  R
Executes P, pushes result R on stack.
*/
void app11_(pEnv env)
{
    PARM(3, DIP);
    code(env, popd_);
    app1_(env);
}
#endif
