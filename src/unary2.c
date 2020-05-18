/*
    module  : unary2.c
    version : 1.17
    date    : 03/28/20
*/
#ifndef UNARY2_C
#define UNARY2_C

#ifndef OLD_RUNTIME
int put_unary2(void)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* UNARY2 */");
    fprintf(outfp, "Node temp, *top, result[2];");
    fprintf(outfp, "temp = *stk; POP(stk); top = stk->next;");
    compile(prog);
    fprintf(outfp, "result[0] = *stk; stk = top;");
    fprintf(outfp, "DUPLICATE(&temp);");
    compile(prog);
    fprintf(outfp, "result[1] = *stk; stk = top;");
    fprintf(outfp, "DUPLICATE(&result[0]);");
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

#ifndef OLD_RUNTIME
    if (compiling && put_unary2())
	return;
    COMPILE;
#endif
    THREEPARAMS("unary2");
    ONEQUOTE("unary2");
    prog = stk->u.lis;
    POP(stk);
    temp = *stk;
    POP(stk);
    top = stk->next;
    exeterm(prog);
    result[0] = *stk;
    stk = top;
    DUPLICATE(&temp);
    exeterm(prog);
    result[1] = *stk;
    stk = top;
    DUPLICATE(&result[0]);
    DUPLICATE(&result[1]);
}
#endif
