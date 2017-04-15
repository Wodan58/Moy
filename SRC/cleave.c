/*
    module  : cleave.c
    version : 1.7
    date    : 04/15/17
*/
#include "runtime.h"

#ifndef NCHECK
int put_cleave(void)
{
    void *save;
    Node *prog[2];
    unsigned op0, op1, op2, op3;

    del_history(2);
    if (!(LIST_1 && LIST_2))
	return 0;
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* CLEAVE */");
    fprintf(outfp, "Node result[2], *save;");
    fprintf(outfp, "CONDITION; save = stk;");
    save = new_history();
    evaluate2(prog[0], START_SCOPE);
    op0 = top_history(&op1);
    old_history(save);
    fprintf(outfp, "result[0] = *stk; stk = save; RELEASE; CONDITION;");
    evaluate2(prog[1], END_SCOPE);
    op2 = top_history(&op3);
    old_history(save);
    add_history2(op0, op1);
    add_history2(op2, op3);
    fprintf(outfp, "result[1] = *stk; stk = save; RELEASE; POP(stk);");
    fprintf(outfp, "DUPLICATE(&result[0]);");
    fprintf(outfp, "DUPLICATE(&result[1]); }");
    return 1;
}
#endif

/*
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
