/*
    module  : dip.c
    version : 1.10
    date    : 07/15/18
*/
#ifndef DIP_X
#define DIP_C

#ifdef NEW_RUNTIME
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
#ifndef OLD_RUNTIME
int put_dip(void)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* DIP */");
    if (new_version)
	fprintf(outfp, "node_t temp; temp = do_pop();");
    else
	fprintf(outfp, "Node temp = *stk; POP(stk);");
    compile(prog);
    if (new_version)
	fprintf(outfp, "do_push(temp); }");
    else
	fprintf(outfp, "DUPLICATE(&temp); }");
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

#ifndef OLD_RUNTIME
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
#endif
