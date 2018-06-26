/*
    module  : branch.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

#ifndef NCHECK
int put_branch(void)
{
    void *save;
    Node *prog[2];

    del_history(3);
    if (!(LIST_1 && LIST_2))
	return 0;
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    printstack(outfp);
    fprintf(outfp, "{ /* BRANCH */");
    fprintf(outfp, "int num = stk->u.num; POP(stk);");
    fprintf(outfp, "if (num) {");
    save = new_history();
    evaluate(prog[0]);
    old_history(save);
    fprintf(outfp, "} else {");
    evaluate(prog[1]);
    fprintf(outfp, "} }");
    return 1;
}
#endif

/**
branch  :  B [T] [F]  ->  ...
If B is true, then executes T else executes F.
*/
PRIVATE void do_branch(void)
{
    int num;
    Node *prog[2];

#ifndef NCHECK
    if (optimizing && put_branch())
	return;
    COMPILE;
    THREEPARAMS("branch");
    TWOQUOTES("branch");
#endif
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    num = stk->u.num;
    POP(stk);
    exeterm(num ? prog[0] : prog[1]);
}