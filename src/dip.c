/*
    module  : dip.c
    version : 1.8
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_dip(void)
{
    node_t temp;
    code_t *prog;

    TRACE;
    prog = (code_t *)do_pop();
    temp = do_pop();
    execute(prog);
    do_push(temp);
}
#else
#ifndef NCHECK
int put_dip(void)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* DIP */ TRACE;");
#ifdef NEW_VERSION
    fprintf(outfp, "node_t temp = do_pop();");
    compile(prog);
    fprintf(outfp, "do_push(temp); }");
#else
    fprintf(outfp, "Node temp = *stk; POP(stk);");
    compile(prog);
    fprintf(outfp, "DUPLICATE(&temp); }");
#endif
    return 1;
}
#endif

/**
dip  :  X [P]  ->  ...  X
Saves X, executes P, pushes X back.
*/
PRIVATE void do_dip(void)
{
    Node *prog, temp;

#ifndef NCHECK
    if (compiling && put_dip())
	return;
    COMPILE;
#endif
    TWOPARAMS("dip");
    ONEQUOTE("dip");
    prog = stk->u.lis;
    POP(stk);
    temp = *stk;
    POP(stk);
    exeterm(prog);
    DUPLICATE(&temp);
}
#endif
