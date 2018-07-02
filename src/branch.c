/*
    module  : branch.c
    version : 1.6
    date    : 07/02/18
*/

#ifndef NCHECK
int put_branch(void)
{
    Node *prog[2];

    if (!(LIST_1 && LIST_2))
	return 0;
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    printstack(outfp);
    fprintf(outfp, "{ /* BRANCH */");
    fprintf(outfp, "int num = stk->u.num; POP(stk);");
    fprintf(outfp, "if (num) {");
    compile(prog[0]);
    fprintf(outfp, "} else {");
    compile(prog[1]);
    fprintf(outfp, "} }");
    return 1;
}
#endif

/**
branch  :  B [T] [F]  ->  ...
If B is true, then executes T else executes F.
*/
PRIVATE void do_branch(void)
{
    int num;
    Node *prog[2];

#ifndef NCHECK
    if (compiling && put_branch())
	return;
    COMPILE;
#endif
    THREEPARAMS("branch");
    TWOQUOTES("branch");
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    num = stk->u.num;
    POP(stk);
    exeterm(num ? prog[0] : prog[1]);
}
