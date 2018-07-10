/*
    module  : unary2.c
    version : 1.15
    date    : 07/10/18
*/
#ifndef UNARY2_X
#define UNARY2_C

#ifdef RUNTIME
void do_unary2(void)
{
    code_t *prog;
    node_t temp, result[2];

    TRACE;
    prog = (code_t *)do_pop();
    temp = do_pop();		// X2
    execute(prog);
    result[0] = stk[-1];	// first result
    stk[-1] = temp;		// restore X2
    execute(prog);
    result[1] = stk[-1];	// second result
    stk[-1] = result[0];
    do_push(result[1]);
}
#else
#ifndef NCHECK
int put_unary2(void)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* UNARY2 */");
#ifdef NEW_VERSION
    fprintf(outfp, "node_t temp, result[2]; TRACE; temp = do_pop();");
    compile(prog);
    fprintf(outfp, "result[0] = stk[-1]; stk[-1] = temp;");
    compile(prog);
    fprintf(outfp, "result[1] = stk[-1]; stk[-1] = result[0];");
    fprintf(outfp, "do_push(result[1]); }");
#else
    fprintf(outfp, "Node temp, *top, result[2];");
    fprintf(outfp, "temp = *stk; POP(stk); top = stk->next; CONDITION;");
    compile(prog);
    fprintf(outfp, "result[0] = *stk; RELEASE; stk = top;");
    fprintf(outfp, "DUPLICATE(&temp); CONDITION;");
    compile(prog);
    fprintf(outfp, "result[1] = *stk; RELEASE; stk = top;");
    fprintf(outfp, "DUPLICATE(&result[0]);");
    fprintf(outfp, "DUPLICATE(&result[1]); }");
#endif
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
#endif
#endif
