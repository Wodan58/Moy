/*
    module  : times.c
    version : 1.4
    date    : 03/12/17
*/
#include "runtime.h"

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
    fprintf(outfp, "unsigned num = stk->u.num; POP(stk);");
    fprintf(outfp, "while (num--) {");
    evaluate(prog);
    fprintf(outfp, "} }");
    return 1;
}
#endif

/*
times  :  N [P]  ->  ...
N times executes P.
*/
PRIVATE void do_times(void)
{
    Node *prog;
    unsigned num;

#ifndef NCHECK
    if (optimizing && put_times())
	return;
    COMPILE;
    TWOPARAMS("times");
    ONEQUOTE("times");
    INTEGER2("times");
#endif
    prog = stk->u.lis;
    POP(stk);
    num = stk->u.num;
    POP(stk);
    while (num--)
	exeterm(prog);
}
