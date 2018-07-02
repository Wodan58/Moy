/*
    module  : i.c
    version : 1.6
    date    : 07/02/18
*/

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
