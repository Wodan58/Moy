/*
    module  : quit.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef QUIT_C
#define QUIT_C

/**
OK 3160  quit  :  N	->
Exit from Joy.
*/
static int exit_index;
static void (*table[DISPLAYMAX])(pEnv);

PUBLIC void my_atexit(void (*proc)(pEnv))
{
#if 0
    if (exit_index == DISPLAYMAX)
	return;
#endif
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
