/*
    module  : quit.c
    version : 1.11
    date    : 03/05/24
*/
#ifndef QUIT_C
#define QUIT_C

/**
Q0  OK  3130  quit  :  N  ->
Exit from Joy.
*/
static int exit_index;
static void (*table[DISPLAYMAX])(pEnv);

PUBLIC void my_atexit(void (*proc)(pEnv))
{
    if (exit_index == DISPLAYMAX)
	return;
    table[exit_index++] = proc;
}

PRIVATE void my_exit(pEnv env)
{
    while (--exit_index >= 0)
	(*table[exit_index])(env);
}

PUBLIC void quit_(pEnv env)
{
    my_exit(env);
    exit(EXIT_SUCCESS);
}
#endif
