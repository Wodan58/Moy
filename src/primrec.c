/*
    module  : primrec.c
    version : 1.8
    date    : 06/25/18
*/
#include "runtime.h"

#ifndef NCHECK
int put_primrec(void)
{
    unsigned op, op1;
    Node *prog, *init;

    del_history(2);
    if (!(LIST_1 && LIST_2))
	return 0;
    prog = stk->u.lis;
    POP(stk);
    init = stk->u.lis;
    POP(stk);
    printstack(outfp);
    if ((op = pop_history(&op1)) == LIST_) {
	fprintf(outfp, "{ /* PRIMREC-LIST */");
	fprintf(outfp, "unsigned num = 0; Node *cur;");
	fprintf(outfp, "assert(stk->op == LIST_);");
	fprintf(outfp, "cur = stk; POP(stk);");
	fprintf(outfp, "for (cur = cur->u.lis; cur; cur = cur->next, num++)");
	fprintf(outfp, "DUPLICATE(cur);");
    } else if (op == STRING_) {
	fprintf(outfp, "{ /* PRIMREC-STRING */");
	fprintf(outfp, "unsigned num = 0; Node *cur; char *str;");
	fprintf(outfp, "assert(stk->op == STRING_);");
	fprintf(outfp, "cur = stk; POP(stk);");
	fprintf(outfp, "for (num = strlen(str = cur->u.str); *str; str++)");
	fprintf(outfp, "PUSH(CHAR_, (long_t)*str);");
    } else if (op == SET_) {
	fprintf(outfp, "{ /* PRIMREC-SET */");
	fprintf(outfp, "unsigned i, num = 0; Node *cur; ulong_t set;");
	fprintf(outfp, "assert(stk->op == SET_);");
	fprintf(outfp, "cur = stk; POP(stk);");
	fprintf(outfp, "set = cur->u.set;");
	fprintf(outfp, "for (num = i = 0; i < SETSIZE_; i++)");
	fprintf(outfp, "if (set & (1 << i)) {");
	fprintf(outfp, "PUSH(INTEGER_, i); num++; }");
    } else if (op == INTEGER_) {
	fprintf(outfp, "{ /* PRIMREC-INTEGER */");
	fprintf(outfp, "unsigned i, num = 0; Node *cur;");
	fprintf(outfp, "assert(stk->op == INTEGER_);");
	fprintf(outfp, "cur = stk; POP(stk);");
	fprintf(outfp, "for (num = i = cur->u.num; i; i--)");
	fprintf(outfp, "PUSH(INTEGER_, i);");
    } else {
	fprintf(outfp, "{ /* PRIMREC-GENERIC */");
	fprintf(outfp, "unsigned i, num = 0; Node *cur;");
	fprintf(outfp, "char *str; ulong_t set;");
	fprintf(outfp, "cur = stk; POP(stk);");
	fprintf(outfp, "switch (cur->op) {");
	fprintf(outfp, "case LIST_:");
	fprintf(outfp, "for (cur = cur->u.lis; cur; cur = cur->next, num++)");
	fprintf(outfp, "DUPLICATE(cur); break;");
	fprintf(outfp, "case STRING_:");
	fprintf(outfp, "for (num = strlen(str = cur->u.str); *str; str++)");
	fprintf(outfp, "PUSH(CHAR_, (long_t)*str); break;");
	fprintf(outfp, "case SET_:");
	fprintf(outfp, "set = cur->u.set;");
	fprintf(outfp, "for (num = i = 0; i < SETSIZE_; i++)");
	fprintf(outfp, "if (set & (1 << i)) {");
	fprintf(outfp, "PUSH(INTEGER_, i); num++; } break;");
	fprintf(outfp, "case INTEGER_:");
	fprintf(outfp, "for (num = i = cur->u.num; i; i--)");
	fprintf(outfp, "PUSH(INTEGER_, i); break; }");
    }
    add_history(INTEGER_);
    evaluate2(init, START_SCOPE);
    fprintf(outfp, "while (num--) {");
    evaluate2(prog, MID_SCOPE);
    fprintf(outfp, "} }");
    evaluate2(0, END_SCOPE);
    return 1;
}
#endif

/**
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
	for (num = strlen(str = cur->u.str); *str; str++)
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
