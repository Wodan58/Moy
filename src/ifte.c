/*
    module  : ifte.c
    version : 1.10
    date    : 04/30/17
*/
#include "runtime.h"

#ifndef NCHECK
int put_ifte(void)
{
    int arr;
    void *save;
    Node *prog[3];

    del_history(3);
    if (!(LIST_1 && LIST_2 && LIST_3))
	return 0;
    prog[2] = stk->u.lis;
    POP(stk);
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* IFTE */");
    fprintf(outfp, "int num; Node *save;");
    if ((arr = arity(prog[0])) != 0)
	fprintf(outfp, "CONDITION;");
    fprintf(outfp, "save = stk;");
    set_history(0);
    evaluate2(prog[0], START_SCOPE);
    set_history(1);
    fprintf(outfp, "num = stk->u.num; stk = save;");
    if (arr != 0)
	fprintf(outfp, "RELEASE;");
    fprintf(outfp, "if (num) {");
    save = new_history();
    evaluate(prog[1]);
    old_history(save);
    fprintf(outfp, "} else {");
    evaluate2(prog[2], END_SCOPE);
    fprintf(outfp, "} }");
    return 1;
}
#endif

/*
ifte  :  [B] [T] [F]  ->  ...
Executes B. If that yields true, then executes T else executes F.
*/
PRIVATE void do_ifte(void)
{
    Node *prog[3], *save;

#ifndef NCHECK
    if (optimizing && put_ifte())
	return;
    COMPILE;
    THREEPARAMS("ifte");
    THREEQUOTES("ifte");
#endif
    prog[2] = stk->u.lis;
    POP(stk);
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    CONDITION;
    save = stk;
    exeterm(prog[0]);
    prog[0] = stk->u.num ? prog[1] : prog[2];
    stk = save;
    RELEASE;
    exeterm(prog[0]);
}
