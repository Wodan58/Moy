/*
    module  : system.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef SYSTEM_C
#define SYSTEM_C

/**
OK 3040  system  :  D	"command"  ->
Escapes to shell, executes string "command".
The string may cause execution of another program.
When that has finished, the process returns to Joy.
*/
void system_(pEnv env)
{
    Node node;

    PARM(1, STRTOD);
    node = vec_pop(env->stck);
    system(node.u.str);
}
#endif
