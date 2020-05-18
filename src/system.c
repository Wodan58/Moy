/*
    module  : system.c
    version : 1.8
    date    : 03/28/20
*/
#ifndef SYSTEM_C
#define SYSTEM_C

/**
system  :  "command"  ->
Escapes to shell, executes string "command".
The string may cause execution of another program.
When that has finished, the process returns to Joy.
*/
PRIVATE void do_system(void)
{
    char *str;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("system");
    STRING("system");
    str = stk->u.str;
    POP(stk);
    system(str);
}
#endif
