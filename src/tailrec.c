/*
    module  : tailrec.c
    version : 1.12
    date    : 07/02/18
*/

#ifndef NCHECK
int put_tailrec(void)
{
    Node *prog[3];
    unsigned ident;
    FILE *oldfp, *newfp;

    if (!(LIST_1 && LIST_2 && LIST_3))
	return 0;
    prog[2] = stk->u.lis;
    POP(stk);
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(declfp, "void do_tailrec_%d(void);", ident = ++identifier);
    fprintf(outfp, "do_tailrec_%d();", ident);
    oldfp = outfp;
    newfp = outfp = nextfile();
    fprintf(outfp, "void do_tailrec_%d(void) {", ident);
    fprintf(outfp, "int num; Node *save;");
    fprintf(outfp, "for (;;) {");
    fprintf(outfp, "CONDITION;");
    fprintf(outfp, "save = stk;");
    compile(prog[0]);
    fprintf(outfp, "num = stk->u.num; stk = save;");
    fprintf(outfp, "RELEASE;");
    fprintf(outfp, "if (num) {");
    compile(prog[1]);
    fprintf(outfp, "break; }");
    compile(prog[2]);
    fprintf(outfp, "} }\n");
    closefile(newfp);
    outfp = oldfp;
    return 1;
}
#endif

/**
tailrec  :  [P] [T] [R1]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses.
*/
static void tailrec(Node *prog[])
{
    int num;
    Node *save;

tailrec:
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
	goto tailrec;
    }
}

PRIVATE void do_tailrec(void)
{
    Node *prog[3];

#ifndef NCHECK
    if (compiling && put_tailrec())
	return;
    COMPILE;
#endif
    THREEPARAMS("tailrec");
    THREEQUOTES("tailrec");
    prog[2] = stk->u.lis;
    POP(stk);
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    tailrec(prog);
}
