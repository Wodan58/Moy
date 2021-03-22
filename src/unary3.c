/*
    module  : unary3.c
    version : 1.15
    date    : 03/15/21
*/
#ifndef UNARY3_C
#define UNARY3_C

#ifndef OLD_RUNTIME
int put_unary3(pEnv env)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = env->stk->u.lis;
    POP(env->stk);
    printstack(env, outfp);
    fprintf(outfp, "{ /* UNARY3 */");
    fprintf(outfp, "Node first, second, *top, result[3];");
    fprintf(outfp, "second = *env->stk; POP(env->stk); first = *env->stk; POP(env->stk);");
    fprintf(outfp, "top = env->stk->next;");
    compile(env, prog);
    fprintf(outfp, "result[0] = *env->stk; env->stk = top;");
    fprintf(outfp, "DUPLICATE(&first);");
    compile(env, prog);
    fprintf(outfp, "result[1] = *env->stk; env->stk = top;");
    fprintf(outfp, "DUPLICATE(&second);");
    compile(env, prog);
    fprintf(outfp, "result[2] = *env->stk; env->stk = top;");
    fprintf(outfp, "DUPLICATE(&result[0]); DUPLICATE(&result[1]);");
    fprintf(outfp, "DUPLICATE(&result[2]); }");
    return 1;
}
#endif

/**
unary3  :  X1 X2 X3 [P]  ->  R1 R2 R3
Executes P three times, with Xi, returns Ri (i = 1..3).
*/
PRIVATE void do_unary3(pEnv env)
{
    Node *prog, first, second, *top, result[3];

#ifndef OLD_RUNTIME
    if (compiling && put_unary3(env))
	return;
    COMPILE;
#endif
    FOURPARAMS("unary3");
    ONEQUOTE("unary3");
    prog = env->stk->u.lis;
    POP(env->stk);
    second = *env->stk;
    POP(env->stk);
    first = *env->stk;
    POP(env->stk);
    top = env->stk->next;
    exeterm(env, prog);
    result[0] = *env->stk;
    env->stk = top;
    DUPLICATE(&first);
    exeterm(env, prog);
    result[1] = *env->stk;
    env->stk = top;
    DUPLICATE(&second);
    exeterm(env, prog);
    result[2] = *env->stk;
    env->stk = top;
    DUPLICATE(&result[0]);
    DUPLICATE(&result[1]);
    DUPLICATE(&result[2]);
}
#endif
