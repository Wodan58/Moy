/*
    module  : tailrec.c
    version : 1.14
    date    : 07/10/18
*/
#ifndef TAILREC_X
#define TAILREC_C

#ifdef RUNTIME
void tailrec(code_t *prog[])
{
tail:
    execute(prog[0]);
    if (do_pop())
	execute(prog[1]);
    else {
	execute(prog[2]);
	goto tail;
    }
}

void do_tailrec(void)
{
    code_t *prog[3];

    TRACE;
    prog[2] = (code_t *)do_pop();
    prog[1] = (code_t *)do_pop();
    prog[0] = (code_t *)do_pop();
    tailrec(prog);
}
#else
#ifndef NCHECK
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
#ifdef NEW_VERSION
    fprintf(outfp, "for (;;) {");
    compile(prog[0]);
    fprintf(outfp, "if (do_pop()) {");
#else
    fprintf(outfp, "int num; Node *save;");
    fprintf(outfp, "for (;;) {");
    fprintf(outfp, "CONDITION; save = stk;");
    compile(prog[0]);
    fprintf(outfp, "num = stk->u.num; stk = save; RELEASE;");
    fprintf(outfp, "if (num) {");
#endif
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
#endif
#endif
