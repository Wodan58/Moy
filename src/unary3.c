/*
    module  : unary3.c
    version : 1.16
    date    : 06/20/22
*/
#ifndef UNARY3_C
#define UNARY3_C

/**
unary3  :  X1 X2 X3 [P]  ->  R1 R2 R3
Executes P three times, with Xi, returns Ri (i = 1..3).
*/
#ifdef COMPILING
void put_unary3(pEnv env, Node *prog)
{
    fprintf(outfp, "{ /* UNARY3 */");
    fprintf(outfp, "Node *first, *second, *top, *result[3];");
    fprintf(outfp, "second = env->stk; POP(env->stk); first = env->stk;");
    fprintf(outfp, "POP(env->stk); top = env->stk->next;");
    compile(env, prog);
    fprintf(outfp, "result[0] = env->stk; env->stk = top;");
    fprintf(outfp, "DUPLICATE(first);");
    compile(env, prog);
    fprintf(outfp, "result[1] = env->stk; env->stk = top;");
    fprintf(outfp, "DUPLICATE(second);");
    compile(env, prog);
    fprintf(outfp, "result[2] = env->stk; env->stk = top;");
    fprintf(outfp, "DUPLICATE(result[0]); DUPLICATE(result[1]);");
    fprintf(outfp, "DUPLICATE(result[2]); }");
}
#endif

PRIVATE void do_unary3(pEnv env)
{
    Node *prog, *first, *second, *top, *result[3];

    ONEPARAM("unary3");
    ONEQUOTE("unary3");
    prog = env->stk->u.lis;
    POP(env->stk);
    INSTANT(put_unary3);
    THREEPARAMS("unary3");
    second = env->stk;
    POP(env->stk);
    first = env->stk;
    POP(env->stk);
    top = env->stk->next;
    exeterm(env, prog);
    result[0] = env->stk;
    env->stk = top;
    DUPLICATE(first);
    exeterm(env, prog);
    result[1] = env->stk;
    env->stk = top;
    DUPLICATE(second);
    exeterm(env, prog);
    result[2] = env->stk;
    env->stk = top;
    DUPLICATE(result[0]);
    DUPLICATE(result[1]);
    DUPLICATE(result[2]);
}
#endif
