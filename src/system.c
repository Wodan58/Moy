/*
    module  : system.c
    version : 1.6
    date    : 07/10/18
*/
#ifndef SYSTEM_X
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

#ifndef NCHECK
    COMPILE;
#endif
    ONEPARAM("system");
    STRING("system");
    str = stk->u.str;
    POP(stk);
    system(str);
}
#endif
