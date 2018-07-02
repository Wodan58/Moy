/*
    module  : cond.c
    version : 1.11
    date    : 07/02/18
*/

#ifndef NCHECK
int put_cond(void)
{
    Node *cur, *list;

    if (!LIST_1)
	return 0;
    cur = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* COND */");
    fprintf(outfp, "int num = 0; Node *save; for (;;) {");
    for (; cur->next; cur = cur->next) {
	list = cur->u.lis->u.lis;
	fprintf(outfp, "CONDITION;");
	fprintf(outfp, "save = stk;");
	compile(list);
	fprintf(outfp, "num = stk->u.num; stk = save;");
	fprintf(outfp, "RELEASE;");
	fprintf(outfp, "if (num) {");
	compile(cur->u.lis->next);
	fprintf(outfp, "break; }");
    }
    fprintf(outfp, "break; } if (!num) {");
    compile(cur->u.lis);
    fprintf(outfp, "} }");
    return 1;
}
#endif

/**
cond  :  [..[[Bi] Ti]..[D]]  ->  ...
Tries each Bi. If that yields true, then executes Ti and exits.
If no Bi yields true, executes default D.
*/
PRIVATE void do_cond(void)
{
    int num = 0;
    Node *cur, *list, *save;

#ifndef NCHECK
    if (compiling && put_cond())
	return;
    COMPILE;
#endif
    ONEPARAM("cond");
/* must check for QUOTES in list */
    LIST("cond");
    CHECKEMPTYLIST(stk->u.lis, "cond");
    cur = stk->u.lis;
    POP(stk);
    for (; cur->next; cur = cur->next) {
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
    exeterm(num ? cur->u.lis->next : cur->u.lis);
}
