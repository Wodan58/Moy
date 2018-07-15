/*
    module  : times.c
    version : 1.10
    date    : 07/15/18
*/
#ifndef TIMES_X
#define TIMES_C

#ifdef NEW_RUNTIME
void do_times(void)
{
    int num;
    code_t *prog;

    TRACE;
    prog = (code_t *)do_pop();
    num = do_pop();
    while (num--)
	execute(prog);
}
#else
#ifndef OLD_RUNTIME
int put_times(void)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* TIMES */");
    if (new_version)
	fprintf(outfp, "int num; num = do_pop();");
    else
	fprintf(outfp, "int num = stk->u.num; POP(stk);");
    fprintf(outfp, "while (num--) {");
    compile(prog);
    fprintf(outfp, "} }");
    return 1;
}
#endif

/**
times  :  N [P]  ->  ...
N times executes P.
*/
PRIVATE void do_times(void)
{
    int num;
    Node *prog;

#ifndef OLD_RUNTIME
    if (compiling && put_times())
	return;
    COMPILE;
#endif
    TWOPARAMS("times");
    ONEQUOTE("times");
    INTEGER2("times");
    prog = stk->u.lis;
    POP(stk);
    num = stk->u.num;
    POP(stk);
    while (num--)
	exeterm(prog);
}
#endif
#endif
