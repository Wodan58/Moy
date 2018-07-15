/*
    module  : cond.c
    version : 1.14
    date    : 07/15/18
*/
#ifndef COND_X
#define COND_C

#ifdef NEW_RUNTIME
void do_cond(void)
{
    code_t *cur;

    TRACE;
    for (cur = (code_t *)do_pop(); cur->next; cur = cur->next) {
	execute(cur->list->list);
	if (do_pop())
	    break;
    }
    execute(cur->next ? cur->list->next : cur->list);
}
#else
#ifndef OLD_RUNTIME
int put_cond(void)
{
    Node *cur, *list;

    if (!LIST_1)
	return 0;
    cur = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* COND */");
    if (new_version)
	fprintf(outfp, "int num = 0; for (;;) {");
    else
	fprintf(outfp, "int num = 0; Node *save; for (;;) {");
    for (; cur->next; cur = cur->next) {
	if (!new_version)
	    fprintf(outfp, "CONDITION; save = stk;");
	list = cur->u.lis->u.lis;
	compile(list);
	if (new_version)
	    fprintf(outfp, "num = do_pop();");
	else
	    fprintf(outfp, "num = stk->u.num; stk = save; RELEASE;");
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

#ifndef OLD_RUNTIME
    if (compiling && put_cond())
	return;
    COMPILE;
#endif
    ONEPARAM("cond");
/* TODO must check for QUOTES in list */
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
#endif
#endif
