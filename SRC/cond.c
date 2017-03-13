/*
    module  : cond.c
    version : 1.6
    date    : 03/12/17
*/
#include "runtime.h"

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
    evaluate2(0, INIT_SCOPE);
    for ( ; cur->next; cur = cur->next) {
	list = cur->u.lis->u.lis;
	fprintf(outfp, "CONDITION; save = stk;");
	evaluate2(list, MID_SCOPE);
	fprintf(outfp, "num = stk->u.num; stk = save; RELEASE;");
	fprintf(outfp, "if (num) {");
	evaluate1(cur->u.lis->next);
	fprintf(outfp, "break; }");
    }
    evaluate2(0, STOP_SCOPE);
    fprintf(outfp, "break; } if (!num) {");
    evaluate(cur->u.lis);
    fprintf(outfp, "} }");
    return 1;
}
#endif

/*
cond  :  [..[[Bi] Ti]..[D]]  ->  ...
Tries each Bi. If that yields true, then executes Ti and exits.
If no Bi yields true, executes default D.
*/
PRIVATE void do_cond(void)
{
    int num = 0;
    Node *cur, *list, *save;

#ifndef NCHECK
    if (optimizing && put_cond())
	return;
    COMPILE;
    ONEPARAM("cond");
/* must check for QUOTES in list */
    LIST("cond");
    CHECKEMPTYLIST(stk->u.lis, "cond");
#endif
    cur = stk->u.lis;
    POP(stk);
    for ( ; cur->next; cur = cur->next) {
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
