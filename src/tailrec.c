/*
    module  : tailrec.c
    version : 1.16
    date    : 03/28/20
*/
#ifndef TAILREC_C
#define TAILREC_C

#ifndef OLD_RUNTIME
int put_tailrec(void)
{
    static int ident;
    FILE *oldfp;
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
    fprintf(declfp, "void tailrec_%d(void);", ++ident);
    fprintf(outfp, "tailrec_%d();", ident);
    oldfp = outfp;
    outfp = nextfile();
    fprintf(outfp, "void tailrec_%d(void) {", ident);
    fprintf(outfp, "int num; Node *save; for (;;) {");
    fprintf(outfp, "save = stk;");
    compile(prog[0]);
    fprintf(outfp, "num = stk->u.num; stk = save; if (num) {");
    compile(prog[1]);
    fprintf(outfp, "break; }");
    compile(prog[2]);
    fprintf(outfp, "} }\n");
    closefile(outfp);
    outfp = oldfp;
    return 1;
}
#endif

/**
tailrec  :  [P] [T] [R1]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses.
*/
void tailrec(Node *prog[])
{
    int num;
    Node *save;

tailrec:
    save = stk;
    exeterm(prog[0]);
    num = stk->u.num;
    stk = save;
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

#ifndef OLD_RUNTIME
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
#endif
