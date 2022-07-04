/*
    module  : cond.c
    version : 1.20
    date    : 06/20/22
*/
#ifndef COND_C
#define COND_C

/**
cond  :  [..[[Bi] Ti]..[D]]  ->  ...
Tries each Bi. If that yields true, then executes Ti and exits.
If no Bi yields true, executes default D.
*/
#ifdef COMPILING
void put_cond(pEnv env, Node *prog)
{
    fprintf(outfp, "{ /* COND */");
    fprintf(outfp, "int num = 0; Node *save; do {");
    for (; prog->next; prog = prog->next) {
	fprintf(outfp, "save = env->stk;");
	compile(env, prog->u.lis->u.lis);
	fprintf(outfp, "num = env->stk->u.num; env->stk = save;");
	fprintf(outfp, "if (num) {");
	compile(env, prog->u.lis->next);
	fprintf(outfp, "break; }");
    }
    fprintf(outfp, "break; } while (0); if (!num) { env->stk = save;");
    compile(env, prog->u.lis);
    fprintf(outfp, "} }");
}
#endif

PRIVATE void do_cond(pEnv env)
{
    int num = 0;
    Node *prog, *save;

    ONEPARAM("cond");
    LIST("cond");
    prog = env->stk->u.lis;
    CHECKEMPTYLIST(prog, "cond");
/* must check for QUOTES in list */
    for (save = prog; save->next; save = save->next)
	CHECKLIST(save->u.lis->op, "cond");
    POP(env->stk);
    INSTANT(put_cond);
    for (; prog->next; prog = prog->next) {
	save = env->stk;
	exeterm(env, prog->u.lis->u.lis);
	num = env->stk->u.num;
	env->stk = save;
	if (num)
	    break;
    }
    exeterm(env, num ? prog->u.lis->next : prog->u.lis);
}
#endif
