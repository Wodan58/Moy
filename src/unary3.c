/*
    module  : unary3.c
    version : 1.13
    date    : 07/15/18
*/
#ifndef UNARY3_X
#define UNARY3_C

#ifdef NEW_RUNTIME
void do_unary3(void)
{
    code_t *prog;
    node_t temp[2], result[3];

    TRACE;
    prog = (code_t *)do_pop();
    temp[1] = do_pop();		// X3
    temp[0] = do_pop();		// X2
    execute(prog);
    result[0] = stk[-1];	// first result
    stk[-1] = temp[0];		// restore X2
    execute(prog);
    result[1] = stk[-1];	// second result
    stk[-1] = temp[1];		// restore X3
    execute(prog);
    result[2] = stk[-1];
    stk[-1] = result[0];
    do_push(result[1]);
    do_push(result[2]);
}
#else
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
    if (new_version) {
	fprintf(outfp, "node_t temp[2], result[3];");
	fprintf(outfp, "temp[1] = do_pop(); temp[0] = do_pop();");
    } else {
	fprintf(outfp, "Node first, second, *top, result[3];");
	fprintf(outfp, "second = *stk; POP(stk); first = *stk; POP(stk);");
	fprintf(outfp, "top = stk->next; CONDITION;");
    }
    compile(prog);
    if (new_version)
	fprintf(outfp, "result[0] = stk[-1]; stk[-1] = temp[0];");
    else {
	fprintf(outfp, "result[0] = *stk; RELEASE; stk = top;");
	fprintf(outfp, "DUPLICATE(&first); CONDITION;");
    }
    compile(prog);
    if (new_version)
	fprintf(outfp, "result[1] = stk[-1]; stk[-1] = temp[1];");
    else {
	fprintf(outfp, "result[1] = *stk; RELEASE; stk = top;");
	fprintf(outfp, "DUPLICATE(&second); CONDITION;");
    }
    compile(prog);
    if (new_version) {
	fprintf(outfp, "result[2] = stk[-1]; stk[-1] = result[0];");
	fprintf(outfp, "do_push(result[1]); do_push(result[2]); }");
    } else {
	fprintf(outfp, "result[2] = *stk; RELEASE; stk = top;");
	fprintf(outfp, "DUPLICATE(&result[0]); DUPLICATE(&result[1]);");
	fprintf(outfp, "DUPLICATE(&result[2]); }");
    }
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
#endif
#endif
