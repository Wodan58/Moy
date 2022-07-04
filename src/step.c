/*
    module  : step.c
    version : 1.15
    date    : 06/20/22
*/
#ifndef STEP_C
#define STEP_C

/**
step  :  A [P]  ->  ...
Sequentially putting members of aggregate A onto stack,
executes P for each member of A.
*/
#ifdef COMPILING
void put_step(pEnv env, Node *prog)
{
    fprintf(outfp, "{ /* STEP */");
    fprintf(outfp, "char *str, *volatile ptr; long set; int i;");
    fprintf(outfp, "Node *cur = env->stk; POP(env->stk);");
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
    fprintf(outfp, "if (set & ((long)1 << i)) {");
    fprintf(outfp, "PUSH_NUM(INTEGER_, i);");
    compile(env, prog);
    fprintf(outfp, "} break; } }");
}
#endif

PRIVATE void do_step(pEnv env)
{
    int i;
    long set;
    Node *prog, *cur;
    char *str, *volatile ptr;

    ONEPARAM("step");
    ONEQUOTE("step");
    prog = env->stk->u.lis;
    POP(env->stk);
    INSTANT(put_step);
    ONEPARAM("step");
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
	    if (set & ((long)1 << i)) {
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
