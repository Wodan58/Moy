/*
    module  : dip.c
    version : 1.13
    date    : 06/20/22
*/
#ifndef DIP_C
#define DIP_C

/**
dip  :  X [P]  ->  ...  X
Saves X, executes P, pushes X back.
*/
#ifdef COMPILING
void put_dip(pEnv env, Node *prog)
{
    fprintf(outfp, "{ /* DIP */");
    fprintf(outfp, "Node *save = env->stk; POP(env->stk);");
    compile(env, prog);
    fprintf(outfp, "DUPLICATE(save); }");
}
#endif

PRIVATE void do_dip(pEnv env)
{
    Node *prog, *save;

    ONEPARAM("dip");
    ONEQUOTE("dip");
    prog = env->stk->u.lis;
    POP(env->stk);
    INSTANT(put_dip);
    ONEPARAM("dip");
    save = env->stk;
    POP(env->stk);
    exeterm(env, prog);
    DUPLICATE(save);
}
#endif
