/*
    module  : app11.c
    version : 1.3
    date    : 09/11/23
*/
#ifndef APP11_C
#define APP11_C

/**
OK 2450  app11  :  DDDA	X Y [P]  ->  R
Executes P, pushes result R on stack.
*/
void app11_(pEnv env)
{
#ifndef COMPILER
    PARM(3, DIP);
    code(env, popd_);
    app1_(env);
#endif
}
#endif
