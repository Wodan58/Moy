/*
    module  : dip.c
    version : 1.11
    date    : 03/28/20
*/
#ifndef DIP_C
#define DIP_C

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
    fprintf(outfp, "Node temp = *stk; POP(stk);");
    compile(prog);
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
