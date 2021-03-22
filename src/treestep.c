/*
    module  : treestep.c
    version : 1.12
    date    : 03/15/21
*/
#ifndef TREESTEP_C
#define TREESTEP_C

#ifndef OLD_RUNTIME
int put_treestep(pEnv env)
{
    static int ident;
    Node *prog;
    FILE *oldfp;

    if (!LIST_1)
	return 0;
    prog = env->stk->u.lis;
    POP(env->stk);
    printstack(env, outfp);
    fprintf(outfp, "void treestep_%d(pEnv env, Node *item);", ++ident);
    fprintf(outfp, "{ Node *item = env->stk; POP(env->stk);");
    fprintf(outfp, "treestep_%d(env, item); }", ident);
    oldfp = outfp;
    outfp = nextfile();
    fprintf(outfp, "void treestep_%d(pEnv env, Node *item) {", ident);
    fprintf(outfp, "if (item->op != LIST_) { DUPLICATE(item);");
    compile(env, prog);
    fprintf(outfp, "} else ");
    fprintf(outfp, "for (item = item->u.lis; item; item = item->next)");
    fprintf(outfp, "treestep_%d(env, item); }", ident);
    closefile(outfp);
    outfp = oldfp;
    return 1;
}
#endif

/**
treestep  :  T [P]  ->  ...
Recursively traverses leaves of tree T, executes P for each leaf.
*/
void treestep(pEnv env, Node *item, Node *prog)
{
    if (item->op != LIST_) {
	DUPLICATE(item);
	exeterm(env, prog);
    } else for (item = item->u.lis; item; item = item->next)
	treestep(env, item, prog);
}

PRIVATE void do_treestep(pEnv env)
{
    Node *item, *prog;

#ifndef OLD_RUNTIME
    if (compiling && put_treestep(env))
	return;
    COMPILE;
#endif
    TWOPARAMS("treestep");
    ONEQUOTE("treestep");
    prog = env->stk->u.lis;
    POP(env->stk);
    item = env->stk;
    POP(env->stk);
    treestep(env, item, prog);
}
#endif
