/*
    module  : system.c
    version : 1.12
    date    : 09/23/24
*/
#ifndef SYSTEM_C
#define SYSTEM_C

/**
Q0  IGNORE_POP  3020  system  :  D  "command"  ->
[IMPURE] Escapes to shell, executes string "command".
The string may cause execution of another program.
When that has finished, the process returns to Joy.
*/
void system_(pEnv env)
{
    Node node;

    PARM(1, STRTOD);
    node = vec_pop(env->stck);
    (void)system(node.u.str);
}
#endif
