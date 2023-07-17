/*
    module  : quit.c
    version : 1.3
    date    : 07/17/23
*/
#ifndef QUIT_C
#define QUIT_C

/**
OK 3160  quit  :  N	->
Exit from Joy.
*/
#if defined(STATS) || defined(SYMBOLS)
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
#endif

PUBLIC void quit_(pEnv env)
{
#if defined(STATS) || defined(SYMBOLS)
    my_exit(env);
#else
    env->nothing++;
#endif
    exit(EXIT_SUCCESS);
}
#endif
