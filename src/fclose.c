/*
    module  : fclose.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef FCLOSE_C
#define FCLOSE_C

/**
fclose  :  S  ->
Stream S is closed and removed from the stack.
*/
PRIVATE void do_fclose(void)
{
    FILE *fp;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("fclose");
    FILE("fclose");
    if ((fp = stk->u.fil) != 0)
	fclose(fp);
    POP(stk);
}
#endif
