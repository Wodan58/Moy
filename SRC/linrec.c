/*
    module  : linrec.c
    version : 1.7
    date    : 04/15/17
*/
#include "runtime.h"

#ifndef NCHECK
int put_linrec(void)
{
    void *save;
    Node *prog[4];
    unsigned ident;
    FILE *oldfp, *newfp;

    del_history(4);
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
    fprintf(outfp, "void do_linrec_%d(void);", ident = ++identifier);
    fprintf(outfp, "do_linrec_%d();", ident);
    oldfp = outfp;
    newfp = outfp = nextfile();
    fprintf(outfp, "void do_linrec_%d(void) {", ident);
    fprintf(outfp, "int num; Node *save;");
    fprintf(outfp, "CONDITION; save = stk;");
    set_history(0);
    evaluate2(prog[0], START_SCOPE);
    set_history(1);
    fprintf(outfp, "num = stk->u.num; stk = save; RELEASE;");
    fprintf(outfp, "if (num) {");
    save = new_history();
    evaluate(prog[1]);
    old_history(save);
    fprintf(outfp, "} else {");
    evaluate2(prog[2], MID_SCOPE);
    fprintf(outfp, "do_linrec_%d();", ident);
    evaluate2(prog[3], END_SCOPE);
    fprintf(outfp, "} }\n");
    closefile(newfp);
    outfp = oldfp;
    return 1;
}
#endif

/*
linrec  :  [P] [T] [R1] [R2]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses, executes R2.
*/
static void do_linrecaux(Node *prog[])
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
	do_linrecaux(prog);
	exeterm(prog[3]);
    }
}

PRIVATE void do_linrec(void)
{
    Node *prog[4];

#ifndef NCHECK
    if (optimizing && put_linrec())
	return;
    COMPILE;
    FOURPARAMS("linrec");
    FOURQUOTES("linrec");
#endif
    prog[3] = stk->u.lis;
    POP(stk);
    prog[2] = stk->u.lis;
    POP(stk);
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    do_linrecaux(prog);
}
