/*
    module  : primrec.c
    version : 1.5
    date    : 03/12/17
*/
#include "runtime.h"

#ifndef NCHECK
int put_primrec(void)
{
    Node *prog, *init;

    if (!(LIST_1 && LIST_2))
	return 0;
    prog = stk->u.lis;
    POP(stk);
    init = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* PRIMREC */");
    fprintf(outfp, "unsigned i, j = 0; char *str; long_t set;");
    fprintf(outfp, "Node *cur = stk; POP(stk);");
    fprintf(outfp, "switch (cur->op) {");
    fprintf(outfp, "case LIST_:");
    fprintf(outfp, "for (cur = cur->u.lis; cur; cur = cur->next, j++)");
    fprintf(outfp, "DUPLICATE(cur); break;");
    fprintf(outfp, "case STRING_:");
    fprintf(outfp, "for (j = strlen(str = stk->u.str); *str; str++)");
    fprintf(outfp, "PUSH(CHAR_, (long_t)*str); break;");
    fprintf(outfp, "case SET_:");
    fprintf(outfp, "set = cur->u.set;");
    fprintf(outfp, "for (j = i = 0; i < SETSIZE_; i++)");
    fprintf(outfp, "if (set & (1 << i)) {");
    fprintf(outfp, "PUSH(INTEGER_, i); j++; } break;");
    fprintf(outfp, "case INTEGER_:");
    fprintf(outfp, "for (i = j = cur->u.num; i; i--)");
    fprintf(outfp, "PUSH(INTEGER_, i); break; }");
    evaluate2(init, START_SCOPE);
    fprintf(outfp, "while (j--) {");
    evaluate2(prog, MID_SCOPE);
    fprintf(outfp, "} }");
    evaluate2(0, END_SCOPE);
    return 1;
}
#endif

/*
primrec  :  X [I] [C]  ->  R
Executes I to obtain an initial value R0.
For integer X uses increasing positive integers to X, combines by C for new R.
For aggregate X uses successive members and combines by C for new R.
*/
PRIVATE void do_primrec(void)
{
    char *str;
    long_t set;
    unsigned i, num = 0;
    Node *prog, *init, *cur;

#ifndef NCHECK
    if (optimizing && put_primrec())
	return;
    COMPILE;
    THREEPARAMS("primrec");
#endif
    prog = stk->u.lis;
    POP(stk);
    init = stk->u.lis;
    POP(stk);
    cur = stk;
    POP(stk);
    switch (cur->op) {
    case LIST_:
	for (cur = cur->u.lis; cur; cur = cur->next, num++)
	    DUPLICATE(cur);
	break;
    case STRING_:
	for (str = cur->u.str; *str; str++, num++)
	    PUSH(CHAR_, (long_t)*str);
	break;
    case SET_:
	set = cur->u.set;
	for (i = 0; i < SETSIZE_; i++)
	    if (set & (1 << i)) {
		PUSH(INTEGER_, i);
		num++;
	    }
	break;
    case INTEGER_:
	for (i = num = cur->u.num; i; i--)
	    PUSH(INTEGER_, i);
	break;
#ifndef NCHECK
    default:
	BADDATA("primrec");
#endif
    }
    exeterm(init);
    while (num--)
	exeterm(prog);
}
