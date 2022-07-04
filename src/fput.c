/*
    module  : fput.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef FPUT_C
#define FPUT_C

/**
fput  :  S X  ->  S
Writes X to stream S, pops X off stack.
*/
PRIVATE void do_fput(pEnv env)
{
    FILE *fp;
    Node *node;
    int stdout_dup;

    COMPILE;
    TWOPARAMS("fput");
    node = env->stk;
    POP(env->stk);
    FILE("fput");
    fp = env->stk->u.fil;
    if ((stdout_dup = dup(1)) != -1)
	dup2(fileno(fp), 1);
    writefactor(env, node);
    putchar(' ');
    fflush(stdout);
    if (stdout_dup != -1) {
	dup2(stdout_dup, 1);
	close(stdout_dup);
    }
}
#endif
