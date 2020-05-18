/*
    module  : i.c
    version : 1.10
    date    : 03/28/20
*/
#ifndef I_C
#define I_C

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
