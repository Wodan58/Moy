/*
    module  : primrec.c
    version : 1.14
    date    : 03/16/21
*/
#ifndef PRIMREC_C
#define PRIMREC_C

#ifndef OLD_RUNTIME
int put_primrec(pEnv env)
{
    Node *prog, *init;

    if (!(LIST_1 && LIST_2))
	return 0;
    prog = env->stk->u.lis;
    POP(env->stk);
    init = env->stk->u.lis;
    POP(env->stk);
    printstack(env, outfp);
    fprintf(outfp, "{ /* PRIMREC */");
    fprintf(outfp, "int i, num = 0; Node *cur;");
    fprintf(outfp, "char *str, *volatile ptr; ulong_t set;");
    fprintf(outfp, "cur = env->stk; POP(env->stk);");
    fprintf(outfp, "switch (cur->op) {");
    fprintf(outfp, "case LIST_:");
    fprintf(outfp, "for (cur = cur->u.lis; cur; cur = cur->next, num++)");
    fprintf(outfp, "DUPLICATE(cur); break;");
    fprintf(outfp, "case STRING_:");
    fprintf(outfp, "ptr = str = cur->u.str;");
    fprintf(outfp, "for (num = strlen(str); *str; str++)");
    fprintf(outfp, "PUSH_NUM(CHAR_, *str); break;");
    fprintf(outfp, "case SET_:");
    fprintf(outfp, "set = cur->u.set;");
    fprintf(outfp, "for (num = i = 0; i < SETSIZE_; i++)");
    fprintf(outfp, "if (set & ((long_t)1 << i)) {");
    fprintf(outfp, "PUSH_NUM(INTEGER_, i); num++; } break;");
    fprintf(outfp, "case INTEGER_:");
    fprintf(outfp, "for (num = i = cur->u.num; i; i--)");
    fprintf(outfp, "PUSH_NUM(INTEGER_, i); break; }");
    compile(env, init);
    fprintf(outfp, "while (num--) {");
    compile(env, prog);
    fprintf(outfp, "} }");
    return 1;
}
#endif

/**
primrec  :  X [I] [C]  ->  R
Executes I to obtain an initial value R0.
For integer X uses increasing positive integers to X, combines by C for new R.
For aggregate X uses successive members and combines by C for new R.
*/
PRIVATE void do_primrec(pEnv env)
{
    long_t set;
    int i, num = 0;
    Node *prog, *init, *cur;
    char *str, *volatile ptr;

#ifndef OLD_RUNTIME
    if (compiling && put_primrec(env))
	return;
    COMPILE;
#endif
    THREEPARAMS("primrec");
    prog = env->stk->u.lis;
    POP(env->stk);
    init = env->stk->u.lis;
    POP(env->stk);
    cur = env->stk;
    POP(env->stk);
    switch (cur->op) {
    case LIST_:
	for (cur = cur->u.lis; cur; cur = cur->next, num++)
	    DUPLICATE(cur);
	break;
    case STRING_:
	ptr = str = cur->u.str;
	for (num = strlen(str); *str; str++)
	    PUSH_NUM(CHAR_, *str);
	break;
    case SET_:
	set = cur->u.set;
	for (i = 0; i < SETSIZE_; i++)
	    if (set & ((long_t)1 << i)) {
		PUSH_NUM(INTEGER_, i);
		num++;
	    }
	break;
    case INTEGER_:
	for (i = num = cur->u.num; i; i--)
	    PUSH_NUM(INTEGER_, i);
	break;
    default:
	BADDATA("primrec");
	break;
    }
    exeterm(env, init);
    while (num--)
	exeterm(env, prog);
}
#endif
