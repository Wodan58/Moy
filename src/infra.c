/*
    module  : infra.c
    version : 1.11
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_infra(void)
{
    code_t *prog, *list, *save;

    TRACE;
    prog = (code_t *)do_pop();
    list = (code_t *)do_pop();
    save = stk2lst();
    lst2stk(list);
    execute(prog);
    list = stk2lst();
    lst2stk(save);
    do_push((node_t)list);
}
#else
#ifndef NCHECK
int put_infra(void)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* INFRA */");
#ifdef NEW_VERSION
    fprintf(outfp, "code_t *list, *save; TRACE; list = (code_t *)do_pop();");
    fprintf(outfp, "save = stk2lst(); lst2stk(list);");
    compile(prog);
    fprintf(outfp, "list = stk2lst(); lst2stk(save); do_push((node_t)list); }");
#else
    fprintf(outfp, "Node *list, *save;");
    fprintf(outfp, "list = stk->u.lis; POP(stk);");
    fprintf(outfp, "save = stk2lst(); lst2stk(list);");
    compile(prog);
    fprintf(outfp, "list = stk2lst(); lst2stk(save);");
    fprintf(outfp, "PUSH(LIST_, list); }");
#endif
    return 1;
}
#endif

/**
infra  :  L1 [P]  ->  L2
Using list L1 as stack, executes P and returns a new list L2.
The first element of L1 is used as the top of stack,
and after execution of P the top of stack becomes the first element of L2.
*/
PRIVATE void do_infra(void)
{
    Node *prog, *list, *save;

/*
 1. Register the program
 2. Register the list
 3. Make a backup of the stack, starting with save
 4. Empty the stack
 5. Copy the list onto the stack
 6. Execute the program
 7. Collect the stack into the list
 8. Empty the stack
 9. Restore the original stack
10. Put the collected list onto the restored stack
*/
#ifndef NCHECK
    if (compiling && put_infra())
	return;
    COMPILE;
#endif
    TWOPARAMS("infra");
    ONEQUOTE("infra");
    LIST2("infra");
    prog = stk->u.lis;		// 1
    POP(stk);
    list = stk->u.lis;		// 2
    POP(stk);
    save = stk2lst();		// 3, 4
    lst2stk(list);		// 5
    exeterm(prog);		// 6
    list = stk2lst();		// 7, 8
    lst2stk(save);		// 9
    PUSH(LIST_, list);		// 10
}
#endif
