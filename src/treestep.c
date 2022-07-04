/*
    module  : treestep.c
    version : 1.13
    date    : 06/20/22
*/
#ifndef TREESTEP_C
#define TREESTEP_C

/**
treestep  :  T [P]  ->  ...
Recursively traverses leaves of tree T, executes P for each leaf.
*/
#ifdef COMPILING
void put_treestep(pEnv env, Node *prog)
{
    static int ident;
    FILE *oldfp;

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
}
#endif

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

    ONEPARAM("treestep");
    ONEQUOTE("treestep");
    prog = env->stk->u.lis;
    POP(env->stk);
    INSTANT(put_treestep);
    ONEPARAM("treestep");
    item = env->stk;
    POP(env->stk);
    treestep(env, item, prog);
}
#endif
