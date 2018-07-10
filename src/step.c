/*
    module  : step.c
    version : 1.10
    date    : 07/10/18
*/
#ifndef STEP_X
#define STEP_C

#ifdef RUNTIME
void do_step(void)
{
    code_t *prog, *cur;

    TRACE;
    prog = (code_t *)do_pop();
    for (cur = (code_t *)do_pop(); cur; cur = cur->next) {
	do_push(cur->num);
	execute(prog);
    }
}
#else
#ifndef NCHECK
int put_step(void)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* STEP */");
#ifdef NEW_VERSION
    fprintf(outfp, "code_t *cur; TRACE;");
    fprintf(outfp, "for (cur = (code_t *)do_pop(); cur; cur = cur->next) {");
    fprintf(outfp, "do_push(cur->num);");
    compile(prog);
    fprintf(outfp, "} }");
#else
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
#endif
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
    if (compiling && put_step())
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
#ifndef NCHECK
    default:
	BADAGGREGATE("step");
#endif
    }
}
#endif
#endif
