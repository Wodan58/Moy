/*
    module  : system.c
    version : 1.9
    date    : 03/05/24
*/
#ifndef SYSTEM_C
#define SYSTEM_C

/**
Q0  OK  3020  system  :  D  "command"  ->
[IMPURE] Escapes to shell, executes string "command".
The string may cause execution of another program.
When that has finished, the process returns to Joy.
*/
void system_(pEnv env)
{
    int rv;
    Node node;

    PARM(1, STRTOD);
    env->stck = pvec_pop(env->stck, &node);
    if (env->ignore)
	return;
    if ((rv = system(node.u.str)) != 0) {
	fflush(stdout);
	fprintf(stderr, "system: %d\n", rv);
    }
}
#endif
