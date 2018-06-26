/*
    module  : unary4.c
    version : 1.9
    date    : 06/25/18
*/
#include "runtime.h"

#ifndef NCHECK
int put_unary4(void)
{
    int arr;
    Node *prog;

    del_history(1);
    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* UNARY4 */");
    fprintf(outfp, "Node first, second, third, *top, result[4];");
    fprintf(outfp, "third = *stk; POP(stk); second = *stk; POP(stk);");
    fprintf(outfp, "first = *stk; POP(stk); top = stk->next;");
    if ((arr = arity(prog)) != 1)
	fprintf(outfp, "CONDITION;");
    evaluate2(prog, START_SCOPE);
    fprintf(outfp, "result[0] = *stk;");
    if (arr != 1)
	fprintf(outfp, "RELEASE;");
    fprintf(outfp, "stk = top; DUPLICATE(&first);");
    if (arr != 1)
	fprintf(outfp, "CONDITION;");
    evaluate2(prog, MID_SCOPE);
    fprintf(outfp, "result[1] = *stk;");
    if (arr != 1)
	fprintf(outfp, "RELEASE;");
    fprintf(outfp, "stk = top; DUPLICATE(&second);");
    if (arr != 1)
	fprintf(outfp, "CONDITION;");
    evaluate2(prog, MID_SCOPE);
    fprintf(outfp, "result[2] = *stk;");
    if (arr != 1)
	fprintf(outfp, "RELEASE;");
    fprintf(outfp, "stk = top; DUPLICATE(&third);");
    if (arr != 1)
	fprintf(outfp, "CONDITION;");
    evaluate2(prog, END_SCOPE);
    fprintf(outfp, "result[3] = *stk;");
    if (arr != 1)
	fprintf(outfp, "RELEASE;");
    fprintf(outfp, "stk = top; DUPLICATE(&result[0]);");
    fprintf(outfp, "DUPLICATE(&result[1]);");
    fprintf(outfp, "DUPLICATE(&result[2]);");
    fprintf(outfp, "DUPLICATE(&result[3]); }");
    return 1;
}
#endif

/**
unary4  :  X1 X2 X3 X4 [P]  ->  R1 R2 R3 R4
Executes P four times, with Xi, returns Ri (i = 1..4).
*/
PRIVATE void do_unary4(void)
{
    Node *prog, first, second, third, *top, result[4];

#ifndef NCHECK
    if (optimizing && put_unary4())
	return;
    COMPILE;
    FIVEPARAMS("unary4");
    ONEQUOTE("unary4");
#endif
    prog = stk->u.lis;
    POP(stk);
    third = *stk;
    POP(stk);
    second = *stk;
    POP(stk);
    first = *stk;
    POP(stk);
    top = stk->next;
    CONDITION;
    exeterm(prog);
    result[0] = *stk;
    RELEASE;
    stk = top;
    DUPLICATE(&first);
    CONDITION;
    exeterm(prog);
    result[1] = *stk;
    RELEASE;
    stk = top;
    DUPLICATE(&second);
    CONDITION;
    exeterm(prog);
    result[2] = *stk;
    RELEASE;
    stk = top;
    DUPLICATE(&third);
    CONDITION;
    exeterm(prog);
    result[3] = *stk;
    RELEASE;
    stk = top;
    DUPLICATE(&result[0]);
    DUPLICATE(&result[1]);
    DUPLICATE(&result[2]);
    DUPLICATE(&result[3]);
}