/*
    module  : binrec.c
    version : 1.6
    date    : 03/12/17
*/
#include "runtime.h"

#ifndef NCHECK
int put_binrec(void)
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
    fprintf(outfp, "void do_binrec_%d(void);", ident = ++identifier);
    fprintf(outfp, "do_binrec_%d();", ident);
    oldfp = outfp;
    newfp = outfp = nextfile();
    fprintf(outfp, "void do_binrec_%d(void) {", ident);
    if (IS_NOK(prog[0]))
	fprintf(outfp, "Node *save;");
    fprintf(outfp, "int num; Node temp;");
    if (IS_NOK(prog[0]))
	fprintf(outfp, "CONDITION; save = stk;");
    evaluate2(prog[0], START_SCOPE);
    fprintf(outfp, "num = TOPVAL(stk);");
    if (IS_NOK(prog[0]))
	fprintf(outfp, "stk = save; RELEASE;");
    fprintf(outfp, "if (num) {");
    evaluate(prog[1]);
    fprintf(outfp, "} else {");
    evaluate2(prog[2], MID_SCOPE);
    fprintf(outfp, "temp = TOPNODE(stk);\n");
    fprintf(outfp, "do_binrec_%d();", ident);
    fprintf(outfp, "DUPLICATE(&temp);");
    fprintf(outfp, "do_binrec_%d();", ident);
    evaluate2(prog[3], END_SCOPE);
    fprintf(outfp, "} }\n");
    closefile(newfp);
    outfp = oldfp;
    return 1;
}
#endif

/*
binrec  :  [P] [T] [R1] [R2]  ->  ...
Executes P. If that yields true, executes T.
Else uses R1 to produce two intermediates, recurses on both,
then executes R2 to combine their results.
*/
static void do_binrecaux(Node *prog[])
{
    int num;
    Node *save, temp;

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
	temp = *stk;
	POP(stk);
	do_binrecaux(prog);
	DUPLICATE(&temp);
	do_binrecaux(prog);
	exeterm(prog[3]);
    }
}

PRIVATE void do_binrec(void)
{
    Node *prog[4];

#ifndef NCHECK
    if (optimizing && put_binrec())
	return;
    COMPILE;
    FOURPARAMS("binrec");
    FOURQUOTES("binrec");
#endif
    prog[3] = stk->u.lis;
    POP(stk);
    prog[2] = stk->u.lis;
    POP(stk);
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    do_binrecaux(prog);
}
