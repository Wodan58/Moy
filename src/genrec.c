/*
    module  : genrec.c
    version : 1.15
    date    : 07/10/18
*/
#ifndef GENREC_X
#define GENREC_C

#ifndef NCHECK
int put_genrec(void)
{
    static int ident;
    FILE *oldfp;
    Node *prog[4];

    if (!(LIST_1 && LIST_2 && LIST_3 && LIST_4))
	return 0;
    prog[3] = stk->u.lis;
    prog[2] = stk->next->u.lis;
    prog[1] = stk->next->next->u.lis;
    prog[0] = stk->next->next->next->u.lis;
    printstack(outfp);
    fprintf(outfp, "do_cons();");
    fprintf(outfp, "do_cons();");
    fprintf(outfp, "do_cons();");
    fprintf(declfp, "void do_genrec_%d(void);", ++ident);
    fprintf(outfp, "do_genrec_%d();", ident);
    oldfp = outfp;
    outfp = nextfile();
    fprintf(outfp, "void do_genrec_%d(void) {", ident);
    fprintf(outfp, "int num; Node code, *save;");
    fprintf(outfp, "code = *stk; POP(stk);");
    fprintf(outfp, "CONDITION;");
    fprintf(outfp, "save = stk;");
    compile(prog[0]);
    fprintf(outfp, "num = stk->u.num; stk = save;");
    fprintf(outfp, "RELEASE;");
    fprintf(outfp, "if (num) {");
    compile(prog[1]);
    fprintf(outfp, "} else {");
    compile(prog[2]);
    fprintf(outfp, "PUSH(LIST_, code.u.lis); NULLARY(LIST_NEWNODE,");
    fprintf(outfp, "ANON_FUNCT_NEWNODE(do_genrec_%d, 0));", ident);
    fprintf(outfp, "do_cons();");
    compile(prog[3]);
    fprintf(outfp, "} }");
    closefile(outfp);
    outfp = oldfp;
    return 1;
}
#endif

/**
genrec  :  [B] [T] [R1] [R2]  ->  ...
Executes B, if that yields true, executes T.
Else executes R1 and then [[[B] [T] [R1] R2] genrec] R2.
*/
static void genrec(void)
{
    int num;
    Node code, *prog, *save;

    code = *stk;
    prog = stk->u.lis->u.lis;
    POP(stk);
    CONDITION;
    save = stk;
    exeterm(prog);
    num = stk->u.num;
    stk = save;
    RELEASE;
    if (num)
	exeterm(code.u.lis->next->u.lis);
    else {
	exeterm(code.u.lis->next->next->u.lis);
	PUSH(LIST_, code.u.lis);
	NULLARY(LIST_NEWNODE, ANON_FUNCT_NEWNODE(genrec, 0));
	do_cons();
	exeterm(code.u.lis->next->next->next);
    }
}

PRIVATE void do_genrec(void)
{
#ifndef NCHECK
    if (compiling && put_genrec())
	return;
    COMPILE;
#endif
    FOURPARAMS("genrec");
    FOURQUOTES("genrec");
    do_cons();
    do_cons();
    do_cons();
    genrec();
}
#endif
