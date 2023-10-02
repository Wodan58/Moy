/*
    module  : app11.c
    version : 1.5
    date    : 10/02/23
*/
#ifndef APP11_C
#define APP11_C

/**
OK 2450  app11  :  DDDA	X Y [P]  ->  R
Executes P, pushes result R on stack.
*/
void app11_(pEnv env)
{
    PARM(3, DIP);
    code(env, popd_);
    app1_(env);
}
#endif
