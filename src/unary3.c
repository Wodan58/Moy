/*
    module  : unary3.c
    version : 1.8
    date    : 10/23/17
*/
#include "runtime.h"

#ifndef NCHECK
int put_unary3(void)
{
    int arr;
    Node *prog;

    del_history(1);
    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* UNARY3 */");
    fprintf(outfp, "Node first, second, *top, result[3];");
    fprintf(outfp, "second = *stk; POP(stk); first = *stk; POP(stk);");
    fprintf(outfp, "top = stk->next;");
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
    evaluate2(prog, END_SCOPE);
    fprintf(outfp, "result[2] = *stk;");
    if (arr != 1)
	fprintf(outfp, "RELEASE;");
    fprintf(outfp, "stk = top; DUPLICATE(&result[0]);");
    fprintf(outfp, "DUPLICATE(&result[1]);");
    fprintf(outfp, "DUPLICATE(&result[2]); }");
    return 1;
}
#endif

/*
unary3  :  X1 X2 X3 [P]  ->  R1 R2 R3
Executes P three times, with Xi, returns Ri (i = 1..3).
*/
PRIVATE void do_unary3(void)
{
    Node *prog, first, second, *top, result[3];

#ifndef NCHECK
    if (optimizing && put_unary3())
	return;
    COMPILE;
    FOURPARAMS("unary3");
    ONEQUOTE("unary3");
#endif
    prog = stk->u.lis;
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
    DUPLICATE(&result[0]);
    DUPLICATE(&result[1]);
    DUPLICATE(&result[2]);
}
