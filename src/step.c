/*
    module  : step.c
    version : 1.7
    date    : 06/25/18
*/
#include "runtime.h"

#ifndef NCHECK
int put_step(void)
{
    void *save;
    Node *prog;
    unsigned op, op1;

    del_history(1);
    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    if ((op = pop_history(&op1)) == LIST_) {
	add_history(op1);
	fprintf(outfp, "{ /* STEP-LIST */");
	fprintf(outfp, "Node *cur;");
	fprintf(outfp, "assert(stk->op == LIST_);");
	fprintf(outfp, "cur = stk->u.lis; POP(stk);");
	fprintf(outfp, "for (; cur; cur = cur->next) {");
	fprintf(outfp, "DUPLICATE(cur);");
	evaluate(prog);
	fprintf(outfp, "} }");
    } else if (op == STRING_) {
	add_history(CHAR_);
	fprintf(outfp, "{ /* STEP-STRING */");
	fprintf(outfp, "char *str;");
	fprintf(outfp, "assert(stk->op == STRING_);");
	fprintf(outfp, "str = stk->u.str; POP(stk);");
	fprintf(outfp, "for (; *str; str++) {");
	fprintf(outfp, "PUSH(CHAR_, (long_t)*str);");
	evaluate(prog);
	fprintf(outfp, "} }");
    } else if (op == SET_) {
	add_history(INTEGER_);
	fprintf(outfp, "{ /* STEP-SET */");
	fprintf(outfp, "unsigned i; ulong_t set;");
	fprintf(outfp, "assert(stk->op == SET_);");
	fprintf(outfp, "set = stk->u.set; POP(stk);");
	fprintf(outfp, "for (i = 0; i < SETSIZE_; i++)");
	fprintf(outfp, "if (set & (1 << i)) {");
	fprintf(outfp, "PUSH(INTEGER_, i);");
	evaluate(prog);
	fprintf(outfp, "} }");
    } else {
	fprintf(outfp, "{ /* STEP-GENERIC */");
	fprintf(outfp, "char *str; ulong_t set; unsigned i; Node *cur;");
	fprintf(outfp, "cur = stk; POP(stk);");
	fprintf(outfp, "switch (cur->op) {");
	fprintf(outfp, "case LIST_:");
	fprintf(outfp, "for (cur = cur->u.lis; cur; cur = cur->next) {");
	fprintf(outfp, "DUPLICATE(cur);");
	save = new_history();
	add_history(INTEGER_);
	evaluate(prog);
	fprintf(outfp, "} break;");
	fprintf(outfp, "case STRING_:");
	fprintf(outfp, "for (str = cur->u.str; *str; str++) {");
	fprintf(outfp, "PUSH(CHAR_, (long_t)*str);");
	old_history(save);
	add_history(CHAR_);
	evaluate(prog);
	fprintf(outfp, "} break;");
	fprintf(outfp, "case SET_:");
	fprintf(outfp, "for (set = cur->u.set, i = 0; i < SETSIZE_; i++)");
	fprintf(outfp, "if (set & (1 << i)) {");
	fprintf(outfp, "PUSH(INTEGER_, i);");
	old_history(save);
	add_history(INTEGER_);
	evaluate(prog);
	fprintf(outfp, "} break; } }");
    }
    return 1;
}
#endif

/**
step  :  A [P]  ->  ...
Sequentially putting members of aggregate A onto stack,
executes P for each member of A.
*/
PRIVATE void do_step(void)
{
    int i;
    char *str;
    ulong_t set;
    Node *prog, *cur;

#ifndef NCHECK
    if (optimizing && put_step())
	return;
    COMPILE;
    TWOPARAMS("step");
    ONEQUOTE("step");
#endif
    prog = stk->u.lis;
    POP(stk);
    cur = stk;
    POP(stk);
    switch (cur->op) {
    case LIST_:
	for (cur = cur->u.lis; cur; cur = cur->next) {
	    DUPLICATE(cur);
	    exeterm(prog);
	}
	break;
    case STRING_:
	for (str = cur->u.str; str && *str; str++) {
	    PUSH(CHAR_, (long_t)*str);
	    exeterm(prog);
	}
	break;
    case SET_:
	set = cur->u.set;
	for (i = 0; i < SETSIZE_; i++)
	    if (set & (1 << i)) {
		PUSH(INTEGER_, i);
		exeterm(prog);
	    }
	break;
#ifndef NCHECK
    default:
	BADAGGREGATE("step");
#endif
    }
}
