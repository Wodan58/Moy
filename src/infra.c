/*
    module  : infra.c
    version : 1.16
    date    : 03/15/21
*/
#ifndef INFRA_C
#define INFRA_C

#ifndef OLD_RUNTIME
int put_infra(pEnv env)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = env->stk->u.lis;
    POP(env->stk);
    printstack(env, outfp);
    fprintf(outfp, "{ /* INFRA */");
    fprintf(outfp, "Node *list, *save; list = env->stk->u.lis; POP(env->stk);");
    fprintf(outfp, "save = stk2lst(env);");
    fprintf(outfp, "env->stk = 0;");
    fprintf(outfp, "lst2stk(env, list);");
    compile(env, prog);
    fprintf(outfp, "list = stk2lst(env);");
    fprintf(outfp, "env->stk = 0;");
    fprintf(outfp, "lst2stk(env, save);");
    fprintf(outfp, "PUSH_PTR(LIST_, list); }");
    return 1;
}
#endif

/**
infra  :  L1 [P]  ->  L2
Using list L1 as stack, executes P and returns a new list L2.
The first element of L1 is used as the top of stack,
and after execution of P the top of stack becomes the first element of L2.
*/
PRIVATE void do_infra(pEnv env)
{
    Node *prog, *list, *save;

/*
 1. Register the program
 2. Register the list
 3. Make a backup of the stack, starting with save
 4. Empty the stack
 5. Copy the list onto the stack
 6. Execute the program
 7. Collect the stack into a list
 8. Empty the stack
 9. Restore the original stack
10. Put the collected list onto the restored stack
*/
#ifndef OLD_RUNTIME
    if (compiling && put_infra(env))
	return;
    COMPILE;
#endif
    TWOPARAMS("infra");
    ONEQUOTE("infra");
    LIST2("infra");
    prog = env->stk->u.lis;	// 1
    POP(env->stk);
    list = env->stk->u.lis;	// 2
    POP(env->stk);
    save = stk2lst(env);	// 3
    env->stk = 0;		// 4
    lst2stk(env, list);		// 5
    exeterm(env, prog);		// 6
    list = stk2lst(env);	// 7
    env->stk = 0;		// 8
    lst2stk(env, save);		// 9
    PUSH_PTR(LIST_, list);	// 10
}
#endif
