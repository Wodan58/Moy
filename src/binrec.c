/*
    module  : binrec.c
    version : 1.16
    date    : 03/28/20
*/
#ifndef BINREC_C
#define BINREC_C

#ifndef OLD_RUNTIME
int put_binrec(void)
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
    fprintf(declfp, "void binrec_%d(void);", ++ident);
    fprintf(outfp, "binrec_%d();", ident);
    oldfp = outfp;
    outfp = nextfile();
    fprintf(outfp, "void binrec_%d(void) {", ident);
    fprintf(outfp, "int num; Node *save, temp; save = stk;");
    compile(prog[0]);
    fprintf(outfp, "num = stk->u.num; stk = save; if (num) {");
    compile(prog[1]);
    fprintf(outfp, "} else {");
    compile(prog[2]);
    fprintf(outfp, "temp = *stk; POP(stk);\n");
    fprintf(outfp, "binrec_%d();", ident);
    fprintf(outfp, "DUPLICATE(&temp);");
    fprintf(outfp, "binrec_%d();", ident);
    compile(prog[3]);
    fprintf(outfp, "} }\n");
    closefile(outfp);
    outfp = oldfp;
    return 1;
}
#endif

/**
binrec  :  [P] [T] [R1] [R2]  ->  ...
Executes P. If that yields true, executes T.
Else uses R1 to produce two intermediates, recurses on both,
then executes R2 to combine their results.
*/
void binrec(Node *prog[])
{
    int num;
    Node *save, temp;

    save = stk;
    exeterm(prog[0]);
    num = stk->u.num;
    stk = save;
    if (num)
	exeterm(prog[1]);
    else {
	exeterm(prog[2]);
	temp = *stk;
	POP(stk);
	binrec(prog);
	DUPLICATE(&temp);
	binrec(prog);
	exeterm(prog[3]);
    }
}

PRIVATE void do_binrec(void)
{
    Node *prog[4];

#ifndef OLD_RUNTIME
    if (compiling && put_binrec())
	return;
    COMPILE;
#endif
    FOURPARAMS("binrec");
    FOURQUOTES("binrec");
    prog[3] = stk->u.lis;
    POP(stk);
    prog[2] = stk->u.lis;
    POP(stk);
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    binrec(prog);
}
#endif
