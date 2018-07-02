/*
    module  : ifte.c
    version : 1.13
    date    : 07/02/18
*/

#ifndef NCHECK
int put_ifte(void)
{
    Node *prog[3];

    if (!(LIST_1 && LIST_2 && LIST_3))
	return 0;
    prog[2] = stk->u.lis;
    POP(stk);
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* IFTE */");
    fprintf(outfp, "int num; Node *save;");
    fprintf(outfp, "CONDITION;");
    fprintf(outfp, "save = stk;");
    compile(prog[0]);
    fprintf(outfp, "num = stk->u.num; stk = save;");
    fprintf(outfp, "RELEASE;");
    fprintf(outfp, "if (num) {");
    compile(prog[1]);
    fprintf(outfp, "} else {");
    compile(prog[2]);
    fprintf(outfp, "} }");
    return 1;
}
#endif

/**
ifte  :  [B] [T] [F]  ->  ...
Executes B. If that yields true, then executes T else executes F.
*/
PRIVATE void do_ifte(void)
{
    Node *prog[3], *save;

#ifndef NCHECK
    if (compiling && put_ifte())
	return;
    COMPILE;
#endif
    THREEPARAMS("ifte");
    THREEQUOTES("ifte");
    prog[2] = stk->u.lis;
    POP(stk);
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    CONDITION;
    save = stk;
    exeterm(prog[0]);
    prog[0] = stk->u.num ? prog[1] : prog[2];
    stk = save;
    RELEASE;
    exeterm(prog[0]);
}
