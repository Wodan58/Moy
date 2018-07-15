/*
    module  : genrec.c
    version : 1.16
    date    : 07/15/18
*/
#ifndef GENREC_X
#define GENREC_C

#ifndef CONS_C
#undef CONS_X
#include "cons.c"
#define CONS_X
#endif

#ifdef NEW_RUNTIME
void genrec(void)
{
    code_t *code, *list;

    code = (code_t *)do_pop();
    execute(code->list);
    if (do_pop())
	execute(code->next->list);
    else {
	execute(code->next->next->list);
	do_push((node_t)code);
	list = joy_code();
	list->fun = genrec;
	do_push((node_t)list);
	do_cons();
	execute(code->next->next->next);
    }
}

void do_genrec(void)
{
    TRACE;
    do_cons();
    do_cons();
    do_cons();
    genrec();
}
#else
#ifndef OLD_RUNTIME
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
    fprintf(declfp, "void genrec_%d(void);", ++ident);
    fprintf(outfp, "genrec_%d();", ident);
    oldfp = outfp;
    outfp = nextfile();
    fprintf(outfp, "void genrec_%d(void) {", ident);
    if (new_version) {
	fprintf(outfp, "code_t *code, *list;");
	fprintf(outfp, "code = (code_t *)do_pop();");
    } else {
	fprintf(outfp, "int num; Node *code, *save;");
	fprintf(outfp, "code = stk->u.lis; POP(stk);");
	fprintf(outfp, "CONDITION; save = stk;");
    }
    compile(prog[0]);
    if (new_version)
	fprintf(outfp, "if (do_pop()) {");
    else {
	fprintf(outfp, "num = stk->u.num; stk = save;");
	fprintf(outfp, "RELEASE; if (num) {");
    }
    compile(prog[1]);
    fprintf(outfp, "} else {");
    compile(prog[2]);
    if (new_version) {
	fprintf(outfp, "do_push((node_t)code); list = joy_code();");
	fprintf(outfp, "list->fun = genrec_%d; do_push((node_t)list);", ident);
    } else {
	fprintf(outfp, "PUSH(LIST_, code); NULLARY(LIST_NEWNODE,");
	fprintf(outfp, "ANON_FUNCT_NEWNODE(genrec_%d, 0));", ident);
    }
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
void genrec(void)
{
    int num;
    Node *code, *save;

    code = stk->u.lis;
    POP(stk);
    CONDITION;
    save = stk;
    exeterm(code->u.lis);
    num = stk->u.num;
    stk = save;
    RELEASE;
    if (num)
	exeterm(code->next->u.lis);
    else {
	exeterm(code->next->next->u.lis);
	PUSH(LIST_, code);
	NULLARY(LIST_NEWNODE, ANON_FUNCT_NEWNODE(genrec, 0));
	do_cons();
	exeterm(code->next->next->next);
    }
}

PRIVATE void do_genrec(void)
{
#ifndef OLD_RUNTIME
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
#endif
