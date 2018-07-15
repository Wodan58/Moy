/*
    module  : i.c
    version : 1.9
    date    : 07/15/18
*/
#ifndef I_X
#define I_C

#ifdef NEW_RUNTIME
void do_i(void)
{
    TRACE;
    execute((code_t *)do_pop());
}
#else
#ifndef OLD_RUNTIME
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

#ifndef OLD_RUNTIME
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
#endif
