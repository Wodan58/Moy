/*
    module  : dip.c
    version : 1.7
    date    : 07/02/18
*/

#ifndef NCHECK
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
