/*
    module  : cleave.c
    version : 1.13
    date    : 07/10/18
*/
#ifndef CLEAVE_X
#define CLEAVE_C

#ifdef RUNTIME
void do_cleave(void)
{
    code_t *prog[2];
    node_t temp, result[2];

    TRACE;
    prog[1] = (code_t *)do_pop();
    prog[0] = (code_t *)do_pop();
    temp = stk[-1];		// copy X
    execute(prog[0]);
    result[0] = stk[-1];	// first result
    stk[-1] = temp;		// restore X
    execute(prog[1]);
    result[1] = stk[-1];	// second result
    stk[-1] = result[0];
    do_push(result[1]);
}
#else
#ifndef NCHECK
int put_cleave(void)
{
    Node *prog[2];

    if (!(LIST_1 && LIST_2))
	return 0;
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* CLEAVE */");
#ifdef NEW_VERSION
    fprintf(outfp, "node_t temp, result[2]; TRACE; temp = stk[-1];");
    compile(prog[0]);
    fprintf(outfp, "result[0] = stk[-1]; stk[-1] = temp;");
    compile(prog[1]);
    fprintf(outfp, "result[1] = stk[-1]; stk[-1] = result[0];");
    fprintf(outfp, "do_push(result[1]); }");
#else
    fprintf(outfp, "Node result[2], temp = *stk;");
    compile(prog[0]);
    fprintf(outfp, "result[0] = *stk; *stk = temp;");
    compile(prog[1]);
    fprintf(outfp, "result[1] = *stk; *stk = result[0];");
    fprintf(outfp, "DUPLICATE(&result[1]); }");
#endif
    return 1;
}
#endif

/**
cleave  :  X [P1] [P2]  ->  R1 R2
Executes P1 and P2, each with X on top, producing two results.
*/
PRIVATE void do_cleave(void)
{
    Node *prog[2], result[2], temp;

#ifndef NCHECK
    if (compiling && put_cleave())
	return;
    COMPILE;
#endif
    THREEPARAMS("cleave");
    TWOQUOTES("cleave");
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    temp = *stk;		// save X
    exeterm(prog[0]);
    result[0] = *stk;
    *stk = temp;		// restore X
    exeterm(prog[1]);
    result[1] = *stk;
    *stk = result[0];		// push results
    DUPLICATE(&result[1]);
}
#endif
#endif
