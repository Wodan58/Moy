/*
    module  : cond.c
    version : 1.19
    date    : 03/15/21
*/
#ifndef COND_C
#define COND_C

#ifndef OLD_RUNTIME
int put_cond(pEnv env)
{
    Node *cur, *list;

    if (!LIST_1)
	return 0;
    cur = env->stk->u.lis;
    POP(env->stk);
    printstack(env, outfp);
    fprintf(outfp, "{ /* COND */");
    fprintf(outfp, "int num = 0; Node *save; do {");
    for (; cur->next; cur = cur->next) {
	fprintf(outfp, "save = env->stk;");
	list = cur->u.lis->u.lis;
	compile(env, list);
	fprintf(outfp, "num = env->stk->u.num; env->stk = save;");
	fprintf(outfp, "if (num) {");
	compile(env, cur->u.lis->next);
	fprintf(outfp, "break; }");
    }
    fprintf(outfp, "break; } while (0); if (!num) {");
    compile(env, cur->u.lis);
    fprintf(outfp, "} }");
    return 1;
}
#endif

/**
cond  :  [..[[Bi] Ti]..[D]]  ->  ...
Tries each Bi. If that yields true, then executes Ti and exits.
If no Bi yields true, executes default D.
*/
PRIVATE void do_cond(pEnv env)
{
    int num = 0;
    Node *cur, *list, *save;

#ifndef OLD_RUNTIME
    if (compiling && put_cond(env))
	return;
    COMPILE;
#endif
    ONEPARAM("cond");
    LIST("cond");
    CHECKEMPTYLIST(env->stk->u.lis, "cond");
/* must check for QUOTES in list */
    for (cur = env->stk->u.lis; cur->next; cur = cur->next)
	CHECKLIST(cur->u.lis->op, "cond");
    cur = env->stk->u.lis;
    POP(env->stk);
    for (; cur->next; cur = cur->next) {
	list = cur->u.lis->u.lis;
	save = env->stk;
	exeterm(env, list);
	num = env->stk->u.num;
	env->stk = save;
	if (num)
	    break;
    }
    exeterm(env, num ? cur->u.lis->next : cur->u.lis);
}
#endif
