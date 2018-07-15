/*
    module  : system.c
    version : 1.7
    date    : 07/15/18
*/
#ifndef SYSTEM_X
#define SYSTEM_C

#ifdef NEW_RUNTIME
void do_system(void)
{
    TRACE;
    system((char *)do_pop());
}
#else
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
#endif
