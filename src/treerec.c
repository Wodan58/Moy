/*
    module  : treerec.c
    version : 1.10
    date    : 07/15/18
*/
#ifndef TREEREC_X
#define TREEREC_C

#ifndef CONS_C
#undef CONS_X
#include "cons.c"
#define CONS_X
#endif

#ifdef NEW_RUNTIME
void treerec(void)
{
    code_t *code, *prog;

    TRACE;
    if (IS_LIST(stk[-2])) {
	code = (code_t *)stk[-1];
	prog = code->next;
	code = joy_code();
	code->fun = treerec;
	do_push((node_t)code);
	do_cons();
	code = (code_t *)stk[-1];
	execute(prog);
    } else {
	code = (code_t *)do_pop();
	execute(code->list);
    }
}

void do_treerec(void)
{
    TRACE;
    do_cons();
    treerec();
}
#else
#ifndef OLD_RUNTIME
int put_treerec(void)
{
    static int ident;
    FILE *oldfp;
    Node *prog[2];

    if (!(LIST_1 && LIST_2))
	return 0;
    prog[1] = stk->u.lis;
    prog[0] = stk->next->u.lis;
    printstack(outfp);
    fprintf(outfp, "do_cons();");
    fprintf(declfp, "void treerec_%d(void);", ++ident);
    fprintf(outfp, "treerec_%d();", ident);
    oldfp = outfp;
    outfp = nextfile();
    fprintf(outfp, "void treerec_%d(void) {", ident);
    if (new_version) {
	fprintf(outfp, "code_t *code; TRACE; if (IS_LIST(stk[-2])) {");
	fprintf(outfp, "code = joy_code(); code->fun = treerec_%d;", ident);
	fprintf(outfp, "do_push((node_t)code);");
    } else {
	fprintf(outfp, "if (stk->next->op == LIST_) { NULLARY(LIST_NEWNODE,");
	fprintf(outfp, "ANON_FUNCT_NEWNODE(treerec_%d, 0));", ident);
    }
    fprintf(outfp, "do_cons();");
    compile(prog[1]);
    if (new_version)
	fprintf(outfp, "} else { (void)do_pop();");
    else
	fprintf(outfp, "} else { POP(stk);");
    compile(prog[0]);
    fprintf(outfp, "} }");
    closefile(outfp);
    outfp = oldfp;
    return 1;
}
#endif

/**
treerec  :  T [O] [C]  ->  ...
T is a tree. If T is a leaf, executes O. Else executes [[[O] C] treerec] C.
*/
void treerec(void)
{
    Node *save;

    if (stk->next->op == LIST_) {
	NULLARY(LIST_NEWNODE, ANON_FUNCT_NEWNODE(treerec, 0));
	do_cons();
	exeterm(stk->u.lis->u.lis->next);
    } else {
	save = stk;
	POP(stk);
	exeterm(save->u.lis->u.lis);
    }
}

PRIVATE void do_treerec(void)
{
#ifndef OLD_RUNTIME
    if (compiling && put_treerec())
	return;
    COMPILE;
#endif
    THREEPARAMS("treerec");
    TWOQUOTES("treerec");
    do_cons();
    treerec();
}
#endif
#endif
