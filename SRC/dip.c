/*
    module  : dip.c
    version : 1.5
    date    : 04/15/17
*/
#include "runtime.h"

#ifndef NCHECK
int put_dip(void)
{
    Node *prog;
    unsigned op, op1;

    del_history(1);
    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* DIP */");
    fprintf(outfp, "Node temp = *stk; POP(stk);");
    op = pop_history(&op1);
    evaluate(prog);
    add_history2(op, op1);
    fprintf(outfp, "DUPLICATE(&temp); }");
    return 1;
}
#endif

/*
dip  :  X [P]  ->  ...  X
Saves X, executes P, pushes X back.
*/
PRIVATE void do_dip(void)
{
    Node *prog, temp;

#ifndef NCHECK
    if (optimizing && put_dip())
	return;
    COMPILE;
    TWOPARAMS("dip");
    ONEQUOTE("dip");
#endif
    prog = stk->u.lis;
    POP(stk);
    temp = *stk;
    POP(stk);
    exeterm(prog);
    DUPLICATE(&temp);
}
