/*
    module  : unary4.c
    version : 1.16
    date    : 06/20/22
*/
#ifndef UNARY4_C
#define UNARY4_C

/**
unary4  :  X1 X2 X3 X4 [P]  ->  R1 R2 R3 R4
Executes P four times, with Xi, returns Ri (i = 1..4).
*/
#ifdef COMPILING
void put_unary4(pEnv env, Node *prog)
{
    fprintf(outfp, "{ /* UNARY4 */");
    fprintf(outfp, "Node *first, *second, *third, *top, *result[4];");
    fprintf(outfp, "third = env->stk; POP(env->stk);");
    fprintf(outfp, "second = env->stk; POP(env->stk);");
    fprintf(outfp, "first = env->stk; POP(env->stk); top = env->stk->next;");
    compile(env, prog);
    fprintf(outfp, "result[0] = env->stk; env->stk = top;");
    fprintf(outfp, "DUPLICATE(first);");
    compile(env, prog);
    fprintf(outfp, "result[1] = env->stk; env->stk = top;");
    fprintf(outfp, "DUPLICATE(second);");
    compile(env, prog);
    fprintf(outfp, "result[2] = env->stk; env->stk = top;");
    fprintf(outfp, "DUPLICATE(third);");
    compile(env, prog);
    fprintf(outfp, "result[3] = env->stk; env->stk = top;");
    fprintf(outfp, "DUPLICATE(result[0]); DUPLICATE(result[1]);");
    fprintf(outfp, "DUPLICATE(result[2]); DUPLICATE(result[3]); }");
}
#endif

PRIVATE void do_unary4(pEnv env)
{
    Node *prog, *first, *second, *third, *top, *result[4];

    ONEPARAM("unary4");
    ONEQUOTE("unary4");
    prog = env->stk->u.lis;
    POP(env->stk);
    INSTANT(put_unary4);
    FOURPARAMS("unary4");
    third = env->stk;
    POP(env->stk);
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
    DUPLICATE(third);
    exeterm(env, prog);
    result[3] = env->stk;
    env->stk = top;
    DUPLICATE(result[0]);
    DUPLICATE(result[1]);
    DUPLICATE(result[2]);
    DUPLICATE(result[3]);
}
#endif
