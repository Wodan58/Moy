/*
    module  : system.c
    version : 1.10
    date    : 06/20/22
*/
#ifndef SYSTEM_C
#define SYSTEM_C

/**
system  :  "command"  ->
Escapes to shell, executes string "command".
The string may cause execution of another program.
When that has finished, the process returns to Joy.
*/
PRIVATE void do_system(pEnv env)
{
    char *str;

    COMPILE;
    ONEPARAM("system");
    STRING("system");
    str = env->stk->u.str;
    POP(env->stk);
    system(str);
}
#endif
