/*
    module  : iftype.h
    version : 1.9
    date    : 03/15/21
*/
#ifndef OLD_RUNTIME
#define CAT(a, b)	a ## b
#define PUT_PROC(a)	CAT(put_, a)

int PUT_PROC(PROCEDURE)(pEnv env)
{
    Node *prog[2];

    if (!(LIST_1 && LIST_2))
	return 0;
    prog[1] = env->stk->u.lis;
    POP(env->stk);
    prog[0] = env->stk->u.lis;
    POP(env->stk);
    printstack(env, outfp);
    fprintf(outfp, "if (env->stk->op == %d) {", TYP);
    fprintf(outfp, "/* IFTYPE */");
    compile(env, prog[0]);
    fprintf(outfp, "} else {");
    compile(env, prog[1]);
    fprintf(outfp, "}");
    return 1;
}
#endif

PRIVATE void PROCEDURE(pEnv env)
{
    Node *first, *second;

#ifndef OLD_RUNTIME
    if (compiling && PUT_PROC(PROCEDURE)(env))
	return;
    COMPILE;
#endif
    TWOPARAMS(NAME);
    TWOQUOTES(NAME);
    second = env->stk->u.lis;
    POP(env->stk);
    first = env->stk->u.lis;
    POP(env->stk);
    exeterm(env, env->stk->op == TYP ? first : second);
}

#undef PROCEDURE
#undef NAME
#undef TYP
#undef CAT
#undef PUT_PROC
