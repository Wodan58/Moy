/*
    module  : quit.c
    version : 1.10
    date    : 06/20/22
*/
#ifndef QUIT_C
#define QUIT_C

static int exit_index;
static void (*my_table[DISPLAYMAX])(pEnv);

void my_atexit(void (*proc)(pEnv))
{
    if (exit_index == DISPLAYMAX)
	return;
    my_table[exit_index++] = proc;
}

void my_exit(pEnv env)
{
    while (--exit_index >= 0)
	(*my_table[exit_index])(env);
}

/**
quit  :  ->
Exit from Joy.
*/
PRIVATE void do_quit(pEnv env)
{
    my_exit(env);
    exit(0);
}
#endif
