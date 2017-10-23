/*
    module  : genrec.c
    version : 1.10
    date    : 04/30/17
*/
#include "runtime.h"

#ifndef NCHECK
int put_genrec(void)
{
    int arr;
    void *save;
    Node *prog[4];
    unsigned ident;
    FILE *oldfp, *newfp;

    del_history(4);
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
    fprintf(declfp, "void do_genrec_%d(void);", ident = ++identifier);
    fprintf(outfp, "do_genrec_%d();", ident);
    oldfp = outfp;
    newfp = outfp = nextfile();
    fprintf(outfp, "void do_genrec_%d(void) {", ident);
    fprintf(outfp, "int num; Node code, *save;");
    fprintf(outfp, "code = *stk; POP(stk);");
    if ((arr = arity(prog[0])) != 0)
	fprintf(outfp, "CONDITION;");
    fprintf(outfp, "save = stk;");
    set_history(0);
    evaluate2(prog[0], START_SCOPE);
    set_history(1);
    fprintf(outfp, "num = stk->u.num; stk = save;");
    if (arr != 0)
	fprintf(outfp, "RELEASE;");
    fprintf(outfp, "if (num) {");
    save = new_history();
    evaluate(prog[1]);
    old_history(save);
    fprintf(outfp, "} else {");
    evaluate2(prog[2], MID_SCOPE);
    fprintf(outfp, "PUSH(LIST_, code.u.lis); NULLARY(LIST_NEWNODE,");
    fprintf(outfp, "ANON_FUNCT_NEWNODE(do_genrec_%d, 0));", ident);
    fprintf(outfp, "do_cons();");
    evaluate2(prog[3], END_SCOPE);
    fprintf(outfp, "} }");
    closefile(newfp);
    outfp = oldfp;
    return 1;
}
#endif

/*
genrec  :  [B] [T] [R1] [R2]  ->  ...
Executes B, if that yields true, executes T.
Else executes R1 and then [[[B] [T] [R1] R2] genrec] R2.
*/
static void do_genrecaux(void)
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
	NULLARY(LIST_NEWNODE, ANON_FUNCT_NEWNODE(do_genrecaux, 0));
	do_cons();
	exeterm(code.u.lis->next->next->next);
    }
}

PRIVATE void do_genrec(void)
{
#ifndef NCHECK
    if (optimizing && put_genrec())
	return;
    COMPILE;
    FOURPARAMS("genrec");
    FOURQUOTES("genrec");
#endif
    do_cons();
    do_cons();
    do_cons();
    do_genrecaux();
}
