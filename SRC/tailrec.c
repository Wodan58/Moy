/*
    module  : tailrec.c
    version : 1.8
    date    : 04/22/17
*/
#include "runtime.h"

#ifndef NCHECK
int put_tailrec(void)
{
    Node *prog[3];
    unsigned ident;
    FILE *oldfp, *newfp;

    del_history(3);
    if (!(LIST_1 && LIST_2 && LIST_3))
	return 0;
    prog[2] = stk->u.lis;
    POP(stk);
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(declfp, "void do_tailrec_%d(void);", ident = ++identifier);
    fprintf(outfp, "do_tailrec_%d();", ident);
    oldfp = outfp;
    newfp = outfp = nextfile();
    fprintf(outfp, "void do_tailrec_%d(void) {", ident);
    fprintf(outfp, "int num; Node *save;");
    fprintf(outfp, "for (;;) {");
    fprintf(outfp, "CONDITION; save = stk;");
    set_history(0);
    evaluate2(prog[0], START_SCOPE);
    set_history(1);
    fprintf(outfp, "num = stk->u.num; stk = save; RELEASE;");
    fprintf(outfp, "if (num) {");
    evaluate(prog[1]);
    fprintf(outfp, "break; }");
    evaluate2(prog[2], END_SCOPE);
    fprintf(outfp, "} }\n");
    closefile(newfp);
    outfp = oldfp;
    return 1;
}
#endif

/*
tailrec  :  [P] [T] [R1]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses.
*/
static void do_tailrecaux(Node *prog[])
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
    if (optimizing && put_tailrec())
	return;
    COMPILE;
    THREEPARAMS("tailrec");
    THREEQUOTES("tailrec");
#endif
    prog[2] = stk->u.lis;
    POP(stk);
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    do_tailrecaux(prog);
}
