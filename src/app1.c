/*
    module  : app1.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef APP1_X
#define APP1_C

#ifdef NEW_RUNTIME
void do_app1(void)
{
    TRACE;
    execute((code_t *)do_pop());
}
#else
#ifndef OLD_RUNTIME
int put_app1(void)
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
app1  :  X [P]  ->  R
Executes P, pushes result R on stack with X.
*/
PRIVATE void do_app1(void)
{
    Node *prog;

#ifndef OLD_RUNTIME
    if (compiling && put_app1())
	return;
    COMPILE;
#endif
    TWOPARAMS("app1");
    ONEQUOTE("app1");
    prog = stk->u.lis;
    POP(stk);
    exeterm(prog);
}
#endif
#endif
