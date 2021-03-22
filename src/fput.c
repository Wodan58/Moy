/*
    module  : fput.c
    version : 1.10
    date    : 03/15/21
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
    Node temp;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS("fput");
#ifndef NCHECK
    if (env->stk->next->op != FILE_ || !env->stk->next->u.fil)
	execerror("file", "fput");
#endif
    temp = *env->stk;
    POP(env->stk);
    fp = env->stk->u.fil;
    writefactor(env, &temp, fp);
    putc(' ', fp);
}
#endif
