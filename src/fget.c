/*
    module  : fget.c
    version : 1.9
    date    : 07/15/18
*/
#ifndef FGET_X
#define FGET_C

#ifdef NEW_RUNTIME
PRIVATE void do_fget(void)
{
    TRACE;
    redirect((FILE *)stk[-1]);
    readfactor(yylex());
}
#else
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
#endif
