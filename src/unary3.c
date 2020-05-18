/*
    module  : unary3.c
    version : 1.14
    date    : 03/28/20
*/
#ifndef UNARY3_C
#define UNARY3_C

#ifndef OLD_RUNTIME
int put_unary3(void)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* UNARY3 */");
    fprintf(outfp, "Node first, second, *top, result[3];");
    fprintf(outfp, "second = *stk; POP(stk); first = *stk; POP(stk);");
    fprintf(outfp, "top = stk->next;");
    compile(prog);
    fprintf(outfp, "result[0] = *stk; stk = top;");
    fprintf(outfp, "DUPLICATE(&first);");
    compile(prog);
    fprintf(outfp, "result[1] = *stk; stk = top;");
    fprintf(outfp, "DUPLICATE(&second);");
    compile(prog);
    fprintf(outfp, "result[2] = *stk; stk = top;");
    fprintf(outfp, "DUPLICATE(&result[0]); DUPLICATE(&result[1]);");
    fprintf(outfp, "DUPLICATE(&result[2]); }");
    return 1;
}
#endif

/**
unary3  :  X1 X2 X3 [P]  ->  R1 R2 R3
Executes P three times, with Xi, returns Ri (i = 1..3).
*/
PRIVATE void do_unary3(void)
{
    Node *prog, first, second, *top, result[3];

#ifndef OLD_RUNTIME
    if (compiling && put_unary3())
	return;
    COMPILE;
#endif
    FOURPARAMS("unary3");
    ONEQUOTE("unary3");
    prog = stk->u.lis;
    POP(stk);
    second = *stk;
    POP(stk);
    first = *stk;
    POP(stk);
    top = stk->next;
    exeterm(prog);
    result[0] = *stk;
    stk = top;
    DUPLICATE(&first);
    exeterm(prog);
    result[1] = *stk;
    stk = top;
    DUPLICATE(&second);
    exeterm(prog);
    result[2] = *stk;
    stk = top;
    DUPLICATE(&result[0]);
    DUPLICATE(&result[1]);
    DUPLICATE(&result[2]);
}
#endif
