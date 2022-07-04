/*
    module  : unary2.c
    version : 1.19
    date    : 06/20/22
*/
#ifndef UNARY2_C
#define UNARY2_C

/**
unary2  :  X1 X2 [P]  ->  R1 R2
Executes P twice, with X1 and X2 on top of the stack.
Returns the two values R1 and R2.
*/
#ifdef COMPILING
void put_unary2(pEnv env, Node *prog)
{
    fprintf(outfp, "{ /* UNARY2 */");
    fprintf(outfp, "Node *save, *top, *result[2];");
    fprintf(outfp, "save = env->stk; POP(env->stk); top = env->stk->next;");
    compile(env, prog);
    fprintf(outfp, "result[0] = env->stk; env->stk = top;");
    fprintf(outfp, "DUPLICATE(save);");
    compile(env, prog);
    fprintf(outfp, "result[1] = env->stk; env->stk = top;");
    fprintf(outfp, "DUPLICATE(result[0]);");
    fprintf(outfp, "DUPLICATE(result[1]); }");
}
#endif

PRIVATE void do_unary2(pEnv env)
{
    Node *prog, *save, *top, *result[2];

    ONEPARAM("unary2");
    ONEQUOTE("unary2");
    prog = env->stk->u.lis;
    POP(env->stk);
    INSTANT(put_unary2);
    TWOPARAMS("unary2");
    save = env->stk;
    POP(env->stk);
    top = env->stk->next;
    exeterm(env, prog);
    result[0] = env->stk;
    env->stk = top;
    DUPLICATE(save);
    exeterm(env, prog);
    result[1] = env->stk;
    env->stk = top;
    DUPLICATE(result[0]);
    DUPLICATE(result[1]);
}
#endif
