/*
    module  : times.c
    version : 1.8
    date    : 07/05/18
*/
#ifdef RUNTIME
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
#ifndef NCHECK
int put_times(void)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* TIMES */");
#ifdef NEW_VERSION
    fprintf(outfp, "int num; TRACE; num = do_pop();");
#else
    fprintf(outfp, "unsigned num = stk->u.num; POP(stk);");
#endif
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
    Node *prog;
    unsigned num;

#ifndef NCHECK
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
