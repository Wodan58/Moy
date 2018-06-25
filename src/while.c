/*
    module  : while.c
    version : 1.10
    date    : 06/25/18
*/
#include "runtime.h"

#ifndef NCHECK
int put_while(void)
{
    int arr;
    Node *prog[2];

    del_history(2);
    if (!(LIST_1 && LIST_2))
	return 0;
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* WHILE */");
    fprintf(outfp, "int num; Node *save; for (;;) {");
    if ((arr = arity(prog[0])) != 0)
	fprintf(outfp, "CONDITION;");
    fprintf(outfp, "save = stk;");
    set_history(0);
    evaluate2(prog[0], START_SCOPE);
    set_history(1);
    fprintf(outfp, "num = stk->u.num; stk = save;");
    if (arr != 0)
	fprintf(outfp, "RELEASE;");
    fprintf(outfp, "if (!num) break;");
    evaluate2(prog[1], END_SCOPE);
    fprintf(outfp, "} }");
    return 1;
}
#endif

/**
while  :  [B] [D]  ->  ...
While executing B yields true executes D.
*/
PRIVATE void do_while(void)
{
    int num;
    Node *prog, *list, *save;

#ifndef NCHECK
    if (optimizing && put_while())
	return;
    COMPILE;
    TWOPARAMS("while");
    TWOQUOTES("while");
#endif
    prog = stk->u.lis;
    POP(stk);
    list = stk->u.lis;
    POP(stk);
    for (;;) {
	CONDITION;
	save = stk;
	exeterm(list);
	num = stk->u.num;
	stk = save;
	RELEASE;
	if (!num)
	    break;
	exeterm(prog);
    }
}
