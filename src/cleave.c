/*
    module  : cleave.c
    version : 1.9
    date    : 06/25/18
*/
#include "runtime.h"

#ifndef NCHECK
int put_cleave(void)
{
    void *save;
    int arr[2];
    Node *prog[2];
    unsigned op0, op1, op2, op3;

    del_history(2);
    if (!(LIST_1 && LIST_2))
	return 0;
    prog[1] = stk->u.lis;
    arr[1] = arity(prog[1]);
    POP(stk);
    prog[0] = stk->u.lis;
    arr[0] = arity(prog[0]);
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* CLEAVE */");
    fprintf(outfp, "Node result[2], *save;");
    if (arr[0] != 0 && arr[0] != 1)
	fprintf(outfp, "CONDITION;");
    fprintf(outfp, "save = stk;");
    if (arr[0] == 1)
	fprintf(outfp, "do_dup();");
    save = new_history();
    evaluate2(prog[0], START_SCOPE);
    op0 = top_history(&op1);
    old_history(save);
    fprintf(outfp, "result[0] = *stk; stk = save;");
    if (arr[0] != 0 && arr[0] != 1)
	fprintf(outfp, "RELEASE;");
    if (arr[1] != 0 && arr[1] != 1)
	fprintf(outfp, "CONDITION;");
    if (arr[1] == 1)
	fprintf(outfp, "do_dup();");
    evaluate2(prog[1], END_SCOPE);
    op2 = top_history(&op3);
    old_history(save);
    add_history2(op0, op1);
    add_history2(op2, op3);
    fprintf(outfp, "result[1] = *stk; stk = save;");
    if (arr[1] != 0 && arr[1] != 1)
	fprintf(outfp, "RELEASE;");
    fprintf(outfp, "POP(stk); DUPLICATE(&result[0]);");
    fprintf(outfp, "DUPLICATE(&result[1]); }");
    return 1;
}
#endif

/**
cleave  :  X [P1] [P2]  ->  R1 R2
Executes P1 and P2, each with X on top, producing two results.
*/
PRIVATE void do_cleave(void)
{
    Node *prog[2], result[2], *save;

#ifndef NCHECK
    if (optimizing && put_cleave())
	return;
    COMPILE;
    THREEPARAMS("cleave");
    TWOQUOTES("cleave");
#endif
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    CONDITION;
    save = stk;
    exeterm(prog[0]);
    result[0] = *stk;
    stk = save;
    RELEASE;
    CONDITION;
    exeterm(prog[1]);
    result[1] = *stk;
    stk = save;
    RELEASE;
    POP(stk);
    DUPLICATE(&result[0]);
    DUPLICATE(&result[1]);
}
