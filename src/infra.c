/*
    module  : infra.c
    version : 1.18
    date    : 06/20/22
*/
#ifndef INFRA_C
#define INFRA_C

/**
infra  :  L1 [P]  ->  L2
Using list L1 as stack, executes P and returns a new list L2.
The first element of L1 is used as the top of stack,
and after execution of P the top of stack becomes the first element of L2.
*/
#ifdef COMPILING
void put_infra(pEnv env, Node *prog)
{
    fprintf(outfp, "{ /* INFRA */");
    fprintf(outfp, "Node *save, *list = env->stk->u.lis; POP(env->stk);");
    fprintf(outfp, "save = env->stk;");
    fprintf(outfp, "env->stk = list;");
    compile(env, prog);
    fprintf(outfp, "list = env->stk;");
    fprintf(outfp, "env->stk = save;");
    fprintf(outfp, "PUSH_PTR(LIST_, list); }");
}
#endif

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
    ONEPARAM("infra");
    ONEQUOTE("infra");
    prog = env->stk->u.lis;	// 1
    POP(env->stk);
    INSTANT(put_infra);
    ONEPARAM("infra");
    LIST("infra");
    list = env->stk->u.lis;	// 2
    POP(env->stk);
    save = env->stk;		// 3
    env->stk = list;		// 5
    exeterm(env, prog);		// 6
    list = env->stk;		// 7
    env->stk = save;		// 8
    PUSH_PTR(LIST_, list);	// 10
}
#endif
