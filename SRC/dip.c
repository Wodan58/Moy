/*
    module  : dip.c
    version : 1.4
    date    : 03/12/17
*/
#include "runtime.h"

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
    fprintf(outfp, "Node save = *stk; POP(stk);");
    evaluate(prog);
    fprintf(outfp, "DUPLICATE(&save); }");
    return 1;
}
#endif

/*
dip  :  X [P]  ->  ...  X
Saves X, executes P, pushes X back.
*/
PRIVATE void do_dip(void)
{
    Node *prog, save;

#ifndef NCHECK
    if (optimizing && put_dip())
	return;
    COMPILE;
    TWOPARAMS("dip");
    ONEQUOTE("dip");
#endif
    prog = stk->u.lis;
    POP(stk);
    save = *stk;
    POP(stk);
    exeterm(prog);
    DUPLICATE(&save);
}
