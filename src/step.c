/*
    module  : step.c
    version : 1.14
    date    : 03/15/21
*/
#ifndef STEP_C
#define STEP_C

#ifndef OLD_RUNTIME
int put_step(pEnv env)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = env->stk->u.lis;
    POP(env->stk);
    printstack(env, outfp);
    fprintf(outfp, "{ /* STEP */");
    fprintf(outfp, "char *str, *volatile ptr; ulong_t set; int i; Node *cur;");
    fprintf(outfp, "cur = env->stk; POP(env->stk);");
    fprintf(outfp, "switch (cur->op) {");
    fprintf(outfp, "case LIST_:");
    fprintf(outfp, "for (cur = cur->u.lis; cur; cur = cur->next) {");
    fprintf(outfp, "DUPLICATE(cur);");
    compile(env, prog);
    fprintf(outfp, "} break;");
    fprintf(outfp, "case STRING_:");
    fprintf(outfp, "for (ptr = cur->u.str, str = ptr; *str; str++) {");
    fprintf(outfp, "PUSH_NUM(CHAR_, *str);");
    compile(env, prog);
    fprintf(outfp, "} break;");
    fprintf(outfp, "case SET_:");
    fprintf(outfp, "for (set = cur->u.set, i = 0; i < SETSIZE_; i++)");
    fprintf(outfp, "if (set & ((long_t)1 << i)) {");
    fprintf(outfp, "PUSH_NUM(INTEGER_, i);");
    compile(env, prog);
    fprintf(outfp, "} break; } }");
    return 1;
}
#endif

/**
step  :  A [P]  ->  ...
Sequentially putting members of aggregate A onto stack,
executes P for each member of A.
*/
PRIVATE void do_step(pEnv env)
{
    int i;
    ulong_t set;
    Node *prog, *cur;
    char *str, *volatile ptr;

#ifndef OLD_RUNTIME
    if (compiling && put_step(env))
	return;
    COMPILE;
#endif
    TWOPARAMS("step");
    ONEQUOTE("step");
    prog = env->stk->u.lis;
    POP(env->stk);
    cur = env->stk;
    POP(env->stk);
    switch (cur->op) {
    case LIST_:
	for (cur = cur->u.lis; cur; cur = cur->next) {
	    DUPLICATE(cur);
	    exeterm(env, prog);
	}
	break;
    case STRING_:
	ptr = cur->u.str;
	for (str = ptr; *str; str++) {
	    PUSH_NUM(CHAR_, *str);
	    exeterm(env, prog);
	}
	break;
    case SET_:
	set = cur->u.set;
	for (i = 0; i < SETSIZE_; i++)
	    if (set & ((long_t)1 << i)) {
		PUSH_NUM(INTEGER_, i);
		exeterm(env, prog);
	    }
	break;
    default:
	BADAGGREGATE("step");
	break;
    }
}
#endif
