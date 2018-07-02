/*
    module  : cleave.c
    version : 1.11
    date    : 07/02/18
*/

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
    fprintf(outfp, "Node result[2], temp;");
    fprintf(outfp, "temp = *stk;");
    compile(prog[0]);
    fprintf(outfp, "result[0] = *stk; *stk = temp;");
    compile(prog[1]);
    fprintf(outfp, "result[1] = *stk; *stk = result[0];");
    fprintf(outfp, "DUPLICATE(&result[1]); }");
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
