/*
    module  : condlinrec.c
    version : 1.12
    date    : 06/29/18
*/
#include "runtime.h"

#ifndef NCHECK
int put_condnestrec(void)
{
    unsigned ident;
    FILE *oldfp, *newfp;
    Node *root, *cur, *list, *node;

    del_history(1);
    if (!LIST_1)
	return 0;
    root = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(declfp, "void do_condnestrec_%d(void);", ident = ++identifier);
    fprintf(outfp, "do_condnestrec_%d();", ident);
    oldfp = outfp;
    newfp = outfp = nextfile();
    fprintf(outfp, "void do_condnestrec_%d(void) {", ident);
    fprintf(outfp, "Node *save; int num;");
    evaluate2(0, INIT_SCOPE);
    for (cur = root; cur->next; cur = cur->next) {
	list = cur->u.lis->u.lis;
	fprintf(outfp, "CONDITION;");
	fprintf(outfp, "save = stk;");
	set_history(0);
	evaluate2(list, MID_SCOPE);
	set_history(1);
	fprintf(outfp, "num = stk->u.num; stk = save;");
	fprintf(outfp, "RELEASE;");
	fprintf(outfp, "if (num) {");
	evaluate2(0, INIT_SCOPE);
	node = cur->u.lis->next;
	evaluate2(node->u.lis, MID_SCOPE);
	while ((node = node->next) != 0) {
	    fprintf(outfp, "do_condnestrec_%d();", ident);
	    evaluate2(node->u.lis, MID_SCOPE);
	}
	fprintf(outfp, "return; }");
	evaluate2(0, STOP_SCOPE);
    }
    cur = cur->u.lis;
    evaluate2(cur->u.lis, MID_SCOPE);
    while ((cur = cur->next) != 0) {
	fprintf(outfp, "do_condnestrec_%d();", ident);
	evaluate2(cur->u.lis, MID_SCOPE);
    }
    fprintf(outfp, "}");
    evaluate2(0, STOP_SCOPE);
    closefile(newfp);
    outfp = oldfp;
    return 1;
}
#endif

PRIVATE void condnestrec(Node *root)
{
    int num = 0;
    Node *cur, *list, *save;

    for (cur = root; cur->next; cur = cur->next) {
	list = cur->u.lis->u.lis;
	CONDITION;
	save = stk;
	exeterm(list);
	num = stk->u.num;
	stk = save;
	RELEASE;
	if (num)
	    break;
    }
    cur = num ? cur->u.lis->next : cur->u.lis;
    exeterm(cur->u.lis);
    while ((cur = cur->next) != 0) {
	condnestrec(root);
	exeterm(cur->u.lis);
    }
}

/**
condlinrec  :  [ [C1] [C2] .. [D] ]  ->  ...
Each [Ci] is of the form [[B] [T]] or [[B] [R1] [R2]].
Tries each B. If that yields true and there is just a [T], executes T and exit.
If there are [R1] and [R2], executes R1, recurses, executes R2.
Subsequent case are ignored. If no B yields true, then [D] is used.
It is then of the form [[T]] or [[R1] [R2]]. For the former, executes T.
For the latter executes R1, recurses, executes R2.
*/
PRIVATE void do_condlinrec(void)
{
    Node *prog;

#ifndef NCHECK
    if (optimizing && put_condnestrec())
	return;
    COMPILE;
    ONEPARAM("condlinrec");
    LIST("condlinrec");
    CHECKEMPTYLIST(stk->u.lis, "condlinrec");
#endif
    prog = stk->u.lis;
    POP(stk);
    condnestrec(prog);
}
