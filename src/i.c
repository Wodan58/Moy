/*
    module  : i.c
    version : 1.7
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_i(void)
{
    TRACE;
    execute((code_t *)do_pop());
}
#else
#ifndef NCHECK
int put_i(void)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    compile(prog);
    return 1;
}
#endif

/**
i  :  [P]  ->  ...
Executes P. So, [P] i  ==  P.
*/
PRIVATE void do_i(void)
{
    Node *prog;

#ifndef NCHECK
    if (compiling && put_i())
	return;
    COMPILE;
#endif
    ONEPARAM("i");
    ONEQUOTE("i");
    prog = stk->u.lis;
    POP(stk);
    exeterm(prog);
}
#endif
