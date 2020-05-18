/*
    module  : condlinrec.c
    version : 1.17
    date    : 03/28/20
*/
#ifndef CONDLINREC_C
#define CONDLINREC_C

#ifndef OLD_RUNTIME
int put_condnestrec(void)
{
    static int ident;
    FILE *oldfp;
    Node *root, *cur, *list, *node;

    if (!LIST_1)
	return 0;
    root = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(declfp, "void condnestrec_%d(void);", ++ident);
    fprintf(outfp, "condnestrec_%d();", ident);
    oldfp = outfp;
    outfp = nextfile();
    fprintf(outfp, "void condnestrec_%d(void) {", ident);
    fprintf(outfp, "Node *save; int num;");
    for (cur = root; cur->next; cur = cur->next) {
	fprintf(outfp, "save = stk;");
	list = cur->u.lis->u.lis;
	compile(list);
	fprintf(outfp, "num = stk->u.num; stk = save; if (num) {");
	node = cur->u.lis->next;
	compile(node->u.lis);
	while ((node = node->next) != 0) {
	    fprintf(outfp, "condnestrec_%d();", ident);
	    compile(node->u.lis);
	}
	fprintf(outfp, "return; }");
    }
    cur = cur->u.lis;
    compile(cur->u.lis);
    while ((cur = cur->next) != 0) {
	fprintf(outfp, "condnestrec_%d();", ident);
	compile(cur->u.lis);
    }
    fprintf(outfp, "}");
    closefile(outfp);
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
	save = stk;
	exeterm(list);
	num = stk->u.num;
	stk = save;
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

#ifndef OLD_RUNTIME
    if (compiling && put_condnestrec())
	return;
    COMPILE;
#endif
    ONEPARAM("condlinrec");
    LIST("condlinrec");
    CHECKEMPTYLIST(stk->u.lis, "condlinrec");
    prog = stk->u.lis;
    POP(stk);
    condnestrec(prog);
}
#endif
