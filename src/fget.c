/*
    module  : fget.c
    version : 1.8
    date    : 07/10/18
*/
#ifndef FGET_X
#define FGET_C

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
#endif
