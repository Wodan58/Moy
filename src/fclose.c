/*
    module  : fclose.c
    version : 1.7
    date    : 07/10/18
*/
#ifndef FCLOSE_X
#define FCLOSE_C

/**
fclose  :  S  ->
Stream S is closed and removed from the stack.
*/
PRIVATE void do_fclose(void)
{
    FILE *fp;

#ifndef NCHECK
    COMPILE;
#endif
    ONEPARAM("fclose");
    FILE("fclose");
    if ((fp = stk->u.fil) != 0)
	fclose(fp);
    POP(stk);
}
#endif
