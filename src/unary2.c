/*
    module  : unary2.c
    version : 1.18
    date    : 03/15/21
*/
#ifndef UNARY2_C
#define UNARY2_C

#ifndef OLD_RUNTIME
int put_unary2(pEnv env)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = env->stk->u.lis;
    POP(env->stk);
    printstack(env, outfp);
    fprintf(outfp, "{ /* UNARY2 */");
    fprintf(outfp, "Node temp, *top, result[2];");
    fprintf(outfp, "temp = *env->stk; POP(env->stk); top = env->stk->next;");
    compile(env, prog);
    fprintf(outfp, "result[0] = *env->stk; env->stk = top;");
    fprintf(outfp, "DUPLICATE(&temp);");
    compile(env, prog);
    fprintf(outfp, "result[1] = *env->stk; env->stk = top;");
    fprintf(outfp, "DUPLICATE(&result[0]);");
    fprintf(outfp, "DUPLICATE(&result[1]); }");
    return 1;
}
#endif

/**
unary2  :  X1 X2 [P]  ->  R1 R2
Executes P twice, with X1 and X2 on top of the stack.
Returns the two values R1 and R2.
*/
PRIVATE void do_unary2(pEnv env)
{
    Node *prog, temp, *top, result[2];

#ifndef OLD_RUNTIME
    if (compiling && put_unary2(env))
	return;
    COMPILE;
#endif
    THREEPARAMS("unary2");
    ONEQUOTE("unary2");
    prog = env->stk->u.lis;
    POP(env->stk);
    temp = *env->stk;
    POP(env->stk);
    top = env->stk->next;
    exeterm(env, prog);
    result[0] = *env->stk;
    env->stk = top;
    DUPLICATE(&temp);
    exeterm(env, prog);
    result[1] = *env->stk;
    env->stk = top;
    DUPLICATE(&result[0]);
    DUPLICATE(&result[1]);
}
#endif
