/*
    module  : construct.c
    version : 1.16
    date    : 03/15/21
*/
#ifndef CONSTRUCT_C
#define CONSTRUCT_C

#ifndef OLD_RUNTIME
int put_construct(pEnv env)
{
    Node *list, *prog;

    if (!(LIST_1 && LIST_2))
	return 0;
    list = env->stk->u.lis;
    POP(env->stk);
    prog = env->stk->u.lis;
    POP(env->stk);
    printstack(env, outfp);
    fprintf(outfp, "{ /* CONSTRUCT */");
    fprintf(outfp, "Node *root = 0, *save[2];");
    fprintf(outfp, "save[0] = stk2lst(env);");
    compile(env, prog);
    for (; list; list = list->next) {
	fprintf(outfp, "save[1] = stk2lst(env);");
	compile(env, list->u.lis);
	fprintf(outfp, "root = newnode(env->stk->op, env->stk->u, root);");
	fprintf(outfp, "env->stk = 0;");
	fprintf(outfp, "lst2stk(env, save[1]);");
	fprintf(outfp, "if (!env->stk) break;");
    }
    fprintf(outfp, "env->stk = 0;");
    fprintf(outfp, "lst2stk(env, save[0]);");
    fprintf(outfp, "root = reverse(root);");
    fprintf(outfp, "while (root) {");
    fprintf(outfp, "DUPLICATE(root);");
    fprintf(outfp, "root = root->next; } }");
    return 1;
}
#endif

/**
construct  :  [P] [[P1] [P2] ..]  ->  R1 R2 ..
Saves state of stack and then executes [P].
Then executes each [Pi] to give Ri pushed onto saved stack.
*/
PRIVATE void do_construct(pEnv env)
{
    Node *list, *prog, *root = 0, *save[2];

#ifndef OLD_RUNTIME
    if (compiling && put_construct(env))
	return;
    COMPILE;
#endif
    TWOPARAMS("construct");
    TWOQUOTES("construct");
    list = env->stk->u.lis;
    POP(env->stk);
    prog = env->stk->u.lis;
    POP(env->stk);
    save[0] = stk2lst(env);
    exeterm(env, prog);
    for (; list; list = list->next) {
	save[1] = stk2lst(env);
	exeterm(env, list->u.lis);
	root = newnode(env->stk->op, env->stk->u, root);
	env->stk = 0;
	lst2stk(env, save[1]);
	if (!env->stk)
	    break;
    }
    env->stk = 0;
    lst2stk(env, save[0]);
    for (list = reverse(root); list; list = list->next)
	DUPLICATE(list);
}
#endif
