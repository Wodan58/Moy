/*
    module  : fget.c
    version : 1.7
    date    : 07/02/18
*/

/**
fget  :  S  ->  S F
Reads a factor from stream S and pushes it onto stack.
*/
PRIVATE void do_fget(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    ONEPARAM("fget");
    if (stk->op != FILE_ || !stk->u.fil)
	execerror("file", "fget");
    redirect(stk->u.fil);
    readfactor(yylex());
}
