/*
    module  : step_str.c
    version : 1.3
    date    : 07/15/18
*/
#ifndef STEP_STR_X
#define STEP_STR_C

#ifdef NEW_RUNTIME
void do_step_str(void)
{
    int i;
    char *str;
    code_t *prog;

    TRACE;
    prog = (code_t *)do_pop();
    if ((str = (char *)do_pop()) == 0)
	return;
    for (i = 0; str[i]; i++) {
	do_push(str[i]);
	execute(prog);
    }
}
#else
#ifndef OLD_RUNTIME
int put_step_str(void)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* STEP_STR */");
    if (new_version) {
	fprintf(outfp, "int i; char *str;");
	fprintf(outfp, "if ((str = (char *)do_pop()) == 0) return;");
	fprintf(outfp, "for (i = 0; str[i]; i++) { do_push(str[i]);");
	compile(prog);
	fprintf(outfp, "} }");
    } else {
	fprintf(outfp, "char *str; ulong_t set; unsigned i; Node *cur;");
	fprintf(outfp, "cur = stk; POP(stk);");
	fprintf(outfp, "switch (cur->op) {");
	fprintf(outfp, "case LIST_:");
	fprintf(outfp, "for (cur = cur->u.lis; cur; cur = cur->next) {");
	fprintf(outfp, "DUPLICATE(cur);");
	compile(prog);
	fprintf(outfp, "} break;");
	fprintf(outfp, "case STRING_:");
	fprintf(outfp, "for (str = cur->u.str; *str; str++) {");
	fprintf(outfp, "PUSH(CHAR_, (long_t)*str);");
	compile(prog);
	fprintf(outfp, "} break;");
	fprintf(outfp, "case SET_:");
	fprintf(outfp, "for (set = cur->u.set, i = 0; i < SETSIZE_; i++)");
	fprintf(outfp, "if (set & (1 << i)) {");
	fprintf(outfp, "PUSH(INTEGER_, i);");
	compile(prog);
	fprintf(outfp, "} break; } }");
    }
    return 1;
}
#endif

/**
step_str  :  A [P]  ->  ...
Sequentially putting members of aggregate A onto stack,
executes P for each member of A.
*/
PRIVATE void do_step_str(void)
{
    int i;
    char *str;
    ulong_t set;
    Node *prog, *cur;

#ifndef OLD_RUNTIME
    if (compiling && put_step_str())
	return;
    COMPILE;
#endif
    TWOPARAMS("step");
    ONEQUOTE("step");
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
    default:
	BADAGGREGATE("step");
	break;
    }
}
#endif
#endif
