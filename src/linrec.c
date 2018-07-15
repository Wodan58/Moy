/*
    module  : linrec.c
    version : 1.15
    date    : 07/15/18
*/
#ifndef LINREC_X
#define LINREC_C

#ifdef NEW_RUNTIME
void linrec(code_t *prog[])
{
    execute(prog[0]);
    if (do_pop())
	execute(prog[1]);
    else {
	execute(prog[2]);
	linrec(prog);
	execute(prog[3]);
    }
}

void do_linrec(void)
{
    code_t *prog[4];

    TRACE;
    prog[3] = (code_t *)do_pop();
    prog[2] = (code_t *)do_pop();
    prog[1] = (code_t *)do_pop();
    prog[0] = (code_t *)do_pop();
    linrec(prog);
}
#else
#ifndef OLD_RUNTIME
int put_linrec(void)
{
    static int ident;
    FILE *oldfp;
    Node *prog[4];

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
    fprintf(declfp, "void linrec_%d(void);", ++ident);
    fprintf(outfp, "linrec_%d();", ident);
    oldfp = outfp;
    outfp = nextfile();
    fprintf(outfp, "void linrec_%d(void) {", ident);
    if (new_version)
	fprintf(outfp, "TRACE;");
    else
	fprintf(outfp, "int num; Node *save; CONDITION; save = stk;");
    compile(prog[0]);
    if (new_version)
	fprintf(outfp, "if (do_pop()) {");
    else
	fprintf(outfp, "num = stk->u.num; stk = save; RELEASE; if (num) {");
    compile(prog[1]);
    fprintf(outfp, "} else {");
    compile(prog[2]);
    fprintf(outfp, "linrec_%d();", ident);
    compile(prog[3]);
    fprintf(outfp, "} }\n");
    closefile(outfp);
    outfp = oldfp;
    return 1;
}
#endif

/**
linrec  :  [P] [T] [R1] [R2]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses, executes R2.
*/
void linrec(Node *prog[])
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

#ifndef OLD_RUNTIME
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
#endif
#endif
