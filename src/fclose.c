/*
    module  : fclose.c
    version : 1.6
    date    : 07/02/18
*/

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
