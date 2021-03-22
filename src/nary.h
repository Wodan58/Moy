/*
    module  : nary.h
    version : 1.15
    date    : 03/15/21
*/
#ifndef OLD_RUNTIME
#define CAT(a, b)	a ## b
#define PUT_PROC(a)	CAT(put_, a)

int PUT_PROC(PROCEDURE)(pEnv env)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = env->stk->u.lis;
    POP(env->stk);
    printstack(env, outfp);
    fprintf(outfp, "{ /* %s */", NAME);
    fprintf(outfp, "Node temp, *top = %s;", TOPSTR);
    compile(env, prog);
    fprintf(outfp, "temp = *env->stk; env->stk = top; DUPLICATE(&temp); }");
    return 1;
}
#endif

PRIVATE void PROCEDURE(pEnv env)
{
    Node *prog, *top, temp;

#ifndef OLD_RUNTIME
    if (compiling && PUT_PROC(PROCEDURE)(env))
	return;
    COMPILE;
#endif
    PARAMCOUNT(NAME);
    ONEQUOTE(NAME);
    prog = env->stk->u.lis;
    POP(env->stk);
    top = TOP;
    exeterm(env, prog);
#ifndef NCHECK
    if (!env->stk)
	execerror("value to push", NAME);
#endif
    temp = *env->stk;
    env->stk = top;
    DUPLICATE(&temp);
}

#undef PROCEDURE
#undef NAME
#undef PARAMCOUNT
#undef TOP
#undef TOPSTR
#undef ARITY
#undef CAT
#undef PUT_PROC
