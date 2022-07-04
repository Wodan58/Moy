/*
    module  : if_type.h
    version : 1.10
    date    : 06/20/22
*/
#ifdef COMPILING
#define CAT(a, b)	a ## b
#define PUT_PROC(a)	CAT(put_, a)

void PUT_PROC(PROCEDURE)(pEnv env, Node *prog[2])
{
    fprintf(outfp, "if (env->stk->op == %d) {", TYP);
    fprintf(outfp, "/* IFTYPE */");
    compile(env, prog[0]);
    fprintf(outfp, "} else {");
    compile(env, prog[1]);
    fprintf(outfp, "}");
}
#endif

PRIVATE void PROCEDURE(pEnv env)
{
    Node *prog[2];

    TWOPARAMS(NAME);
    TWOQUOTES(NAME);
    prog[1] = env->stk->u.lis;
    POP(env->stk);
    prog[0] = env->stk->u.lis;
    POP(env->stk);
    INSTANT(PUT_PROC(PROCEDURE));
    ONEPARAM(NAME);
    exeterm(env, env->stk->op == TYP ? prog[0] : prog[1]);
}

#undef PROCEDURE
#undef NAME
#undef TYP
#undef CAT
#undef PUT_PROC
