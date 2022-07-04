/*
    module  : n_ary.h
    version : 1.16
    date    : 06/20/22
*/
#ifdef COMPILING
#define CAT(a, b)	a ## b
#define PUT_PROC(a)	CAT(put_, a)

void PUT_PROC(PROCEDURE)(pEnv env, Node *prog)
{
    fprintf(outfp, "{ /* %s */", NAME);
    fprintf(outfp, "Node *save, *top = %s;", TOPSTR);
    compile(env, prog);
    fprintf(outfp, "save = env->stk; env->stk = top; DUPLICATE(save); }");
}
#endif

PRIVATE void PROCEDURE(pEnv env)
{
    Node *prog, *save, *top;

    ONEPARAM(NAME);
    ONEQUOTE(NAME);
    prog = env->stk->u.lis;
    POP(env->stk);
    INSTANT(PUT_PROC(PROCEDURE));
    top = TOP;
    exeterm(env, prog);
    CHECKVALUE(NAME);
    save = env->stk;
    env->stk = top;
    DUPLICATE(save);
}

#undef PROCEDURE
#undef NAME
#undef TOP
#undef TOPSTR
#undef CAT
#undef PUT_PROC
