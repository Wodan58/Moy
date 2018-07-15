/*
    module  : unary4.c
    version : 1.13
    date    : 07/15/18
*/
#ifndef UNARY4_X
#define UNARY4_C

#ifdef NEW_RUNTIME
void do_unary4(void)
{
    code_t *prog;
    node_t temp[3], result[4];

    TRACE;
    prog = (code_t *)do_pop();
    temp[2] = do_pop();		// X4
    temp[1] = do_pop();		// X3
    temp[0] = do_pop();		// X2
    execute(prog);
    result[0] = stk[-1];	// first result
    stk[-1] = temp[0];		// restore X2
    execute(prog);
    result[1] = stk[-1];	// second result
    stk[-1] = temp[1];		// restore X3
    execute(prog);
    result[2] = stk[-1];	// third result
    stk[-1] = temp[2];		// restore X4
    execute(prog);
    stk[-1] = result[0];
    do_push(result[1]);
    do_push(result[2]);
    do_push(result[3]);
}
#else
#ifndef OLD_RUNTIME
int put_unary4(void)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* UNARY4 */");
    if (new_version) {
	fprintf(outfp, "node_t temp[3], result[4]; temp[2] = do_pop();");
	fprintf(outfp, "temp[1] = do_pop(); temp[0] = do_pop();");
    } else {
	fprintf(outfp, "Node first, second, third, *top, result[4];");
	fprintf(outfp, "third = *stk; POP(stk); second = *stk; POP(stk);");
	fprintf(outfp, "first = *stk; POP(stk); top = stk->next; CONDITION;");
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
    if (new_version)
	fprintf(outfp, "result[2] = stk[-1]; stk[-1] = temp[2];");
    else {
	fprintf(outfp, "result[2] = *stk; RELEASE; stk = top;");
	fprintf(outfp, "DUPLICATE(&third); CONDITION;");
    }
    compile(prog);
    if (new_version) {
	fprintf(outfp, "stk[-1] = result[0]; do_push(result[1]);");
	fprintf(outfp, "do_push(result[2]); do_push(result[3]); }");
    } else {
	fprintf(outfp, "result[3] = *stk; RELEASE; stk = top;");
	fprintf(outfp, "DUPLICATE(&result[0]); DUPLICATE(&result[1]);");
	fprintf(outfp, "DUPLICATE(&result[2]); DUPLICATE(&result[3]); }");
    }
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

#ifndef OLD_RUNTIME
    if (compiling && put_unary4())
	return;
    COMPILE;
#endif
    FIVEPARAMS("unary4");
    ONEQUOTE("unary4");
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
#endif
#endif
