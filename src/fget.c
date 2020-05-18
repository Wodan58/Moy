/*
    module  : fget.c
    version : 1.10
    date    : 03/28/20
*/
#ifndef FGET_C
#define FGET_C

/**
fget  :  S  ->  S F
Reads a factor from stream S and pushes it onto stack.
*/
PRIVATE void do_fget(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("fget");
#ifndef NCHECK
    if (stk->op != FILE_ || !stk->u.fil)
	execerror("file", "fget");
#endif
    redirect(stk->u.fil);
    readfactor(yylex());
}
#endif
