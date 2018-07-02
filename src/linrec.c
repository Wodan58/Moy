/*
    module  : linrec.c
    version : 1.12
    date    : 07/02/18
*/

#ifndef NCHECK
int put_linrec(void)
{
    Node *prog[4];
    unsigned ident;
    FILE *oldfp, *newfp;

    if (!(LIST_1 && LIST_2 && LIST_3 && LIST_4))
	return 0;
    prog[3] = stk->u.lis;
    POP(stk);
    prog[2] = stk->u.lis;
    POP(stk);
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(declfp, "void do_linrec_%d(void);", ident = ++identifier);
    fprintf(outfp, "do_linrec_%d();", ident);
    oldfp = outfp;
    newfp = outfp = nextfile();
    fprintf(outfp, "void do_linrec_%d(void) {", ident);
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
    fprintf(outfp, "do_linrec_%d();", ident);
    compile(prog[3]);
    fprintf(outfp, "} }\n");
    closefile(newfp);
    outfp = oldfp;
    return 1;
}
#endif

/**
linrec  :  [P] [T] [R1] [R2]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses, executes R2.
*/
static void linrec(Node *prog[])
{
    int num;
    Node *save;

    CONDITION;
    save = stk;
    exeterm(prog[0]);
    num = stk->u.num;
    stk = save;
    RELEASE;
    if (num)
	exeterm(prog[1]);
    else {
	exeterm(prog[2]);
	linrec(prog);
	exeterm(prog[3]);
    }
}

PRIVATE void do_linrec(void)
{
    Node *prog[4];

#ifndef NCHECK
    if (compiling && put_linrec())
	return;
    COMPILE;
#endif
    FOURPARAMS("linrec");
    FOURQUOTES("linrec");
    prog[3] = stk->u.lis;
    POP(stk);
    prog[2] = stk->u.lis;
    POP(stk);
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    linrec(prog);
}
