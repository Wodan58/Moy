/*
    module  : unary2.c
    version : 1.11
    date    : 06/29/18
*/
#include "runtime.h"

#ifndef NCHECK
int put_unary2(void)
{
    Node *prog;

    del_history(1);
    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* UNARY2 */");
    fprintf(outfp, "Node temp, *top, result[2];");
    fprintf(outfp, "temp = *stk; POP(stk); top = stk->next;");
    fprintf(outfp, "CONDITION;");
    evaluate2(prog, START_SCOPE);
    fprintf(outfp, "result[0] = *stk;");
    fprintf(outfp, "RELEASE;");
    fprintf(outfp, "stk = top; DUPLICATE(&temp);");
    fprintf(outfp, "CONDITION;");
    evaluate2(prog, END_SCOPE);
    fprintf(outfp, "result[1] = *stk;");
    fprintf(outfp, "RELEASE;");
    fprintf(outfp, "stk = top; DUPLICATE(&result[0]);");
    fprintf(outfp, "DUPLICATE(&result[1]); }");
    return 1;
}
#endif

/**
unary2  :  X1 X2 [P]  ->  R1 R2
Executes P twice, with X1 and X2 on top of the stack.
Returns the two values R1 and R2.
*/
PRIVATE void do_unary2(void)
{
    Node *prog, temp, *top, result[2];

#ifndef NCHECK
    if (optimizing && put_unary2())
	return;
    COMPILE;
    THREEPARAMS("unary2");
    ONEQUOTE("unary2");
#endif
    prog = stk->u.lis;
    POP(stk);
    temp = *stk;
    POP(stk);
    top = stk->next;
    CONDITION;
    exeterm(prog);
    result[0] = *stk;
    RELEASE;
    stk = top;
    DUPLICATE(&temp);
    CONDITION;
    exeterm(prog);
    result[1] = *stk;
    RELEASE;
    stk = top;
    DUPLICATE(&result[0]);
    DUPLICATE(&result[1]);
}
