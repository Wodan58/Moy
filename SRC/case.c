/*
    module  : case.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

PRIVATE double Compare(Node *first, Node *second, int *error);

#ifndef NCHECK
int put_case(void)
{
    Node *cur;
    unsigned item;

    if (!LIST_1)
	return 0;
    cur = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* CASE */");
    fprintf(outfp, "int num = 0, error; for (;;) {");
    for ( ; cur->next; cur = cur->next) {
	evaluate2(0, INIT_SCOPE);
	item = PrintHead(cur, outfp);
	fprintf(outfp, "if (!Compare(L%d, stk, &error)", item);
	fprintf(outfp, "&& !error) { POP(stk);");
	evaluate(cur->u.lis->next);
	fprintf(outfp, "num = 1; break; }");
	evaluate2(0, STOP_SCOPE);
    }
    fprintf(outfp, "break; } if (!num) {");
    evaluate(cur->u.lis);
    fprintf(outfp, "} }");
    return 1;
}
#endif

/*
case  :  X [..[X Y]..]  ->  Y i
Indexing on the value of X, execute the matching Y.
*/
PRIVATE void do_case(void)
{
    Node *cur;
    int error;

#ifndef NCHECK
    if (optimizing && put_case())
	return;
    COMPILE;
    TWOPARAMS("case");
    LIST("case");
    CHECKEMPTYLIST(stk->u.lis, "case");
#endif
    cur = stk->u.lis;
    POP(stk);
    for ( ; cur->next; cur = cur->next)
	if (!Compare(cur->u.lis, stk, &error) && !error)
	    break;
    if (cur->next) {
	POP(stk);
	exeterm(cur->u.lis->next);
    } else
	exeterm(cur->u.lis);
}
