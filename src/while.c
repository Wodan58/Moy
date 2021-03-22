/*
    module  : while.c
    version : 1.17
    date    : 03/15/21
*/
#ifndef WHILE_C
#define WHILE_C

#ifndef OLD_RUNTIME
int put_while(pEnv env)
{
    Node *prog[2];

    if (!(LIST_1 && LIST_2))
	return 0;
    prog[1] = env->stk->u.lis;
    POP(env->stk);
    prog[0] = env->stk->u.lis;
    POP(env->stk);
    printstack(env, outfp);
    fprintf(outfp, "{ /* WHILE */");
    fprintf(outfp, "int num; Node *save; for (;;) {");
    fprintf(outfp, "save = env->stk;");
    compile(env, prog[0]);
    fprintf(outfp, "num = env->stk->u.num; env->stk = save;");
    fprintf(outfp, "if (!num) break;");
    compile(env, prog[1]);
    fprintf(outfp, "}");
    fprintf(outfp, "}");
    return 1;
}
#endif

/**
while  :  [B] [D]  ->  ...
While executing B yields true executes D.
*/
PRIVATE void do_while(pEnv env)
{
    int num;
    Node *prog, *list, *save;

#ifndef OLD_RUNTIME
    if (compiling && put_while(env))
	return;
    COMPILE;
#endif
    TWOPARAMS("while");
    TWOQUOTES("while");
    prog = env->stk->u.lis;
    POP(env->stk);
    list = env->stk->u.lis;
    POP(env->stk);
    for (;;) {
	save = env->stk;
	exeterm(env, list);
	num = env->stk->u.num;
	env->stk = save;
	if (!num)
	    break;
	exeterm(env, prog);
    }
}
#endif
