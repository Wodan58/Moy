/*
    module  : while.c
    version : 1.18
    date    : 06/20/22
*/
#ifndef WHILE_C
#define WHILE_C

/**
while  :  [B] [D]  ->  ...
While executing B yields true executes D.
*/
#ifdef COMPILING
void put_while(pEnv env, Node *prog[2])
{
    fprintf(outfp, "{ /* WHILE */");
    fprintf(outfp, "int num; Node *save; for (;;) {");
    fprintf(outfp, "save = env->stk;");
    compile(env, prog[0]);
    fprintf(outfp, "num = env->stk->u.num; env->stk = save;");
    fprintf(outfp, "if (!num) break;");
    compile(env, prog[1]);
    fprintf(outfp, "}");
    fprintf(outfp, "}");
}
#endif

PRIVATE void do_while(pEnv env)
{
    int num;
    Node *prog[2], *save;

    TWOPARAMS("while");
    TWOQUOTES("while");
    prog[1] = env->stk->u.lis;
    POP(env->stk);
    prog[0] = env->stk->u.lis;
    POP(env->stk);
    INSTANT(put_while);
    for (;;) {
	save = env->stk;
	exeterm(env, prog[0]);
	num = env->stk->u.num;
	env->stk = save;
	if (!num)
	    break;
	exeterm(env, prog[1]);
    }
}
#endif
