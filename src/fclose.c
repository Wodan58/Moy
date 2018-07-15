/*
    module  : fclose.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef FCLOSE_X
#define FCLOSE_C

#ifdef NEW_RUNTIME
void do_fclose(void)
{
    FILE *fp;

    TRACE;
    if ((fp = (FILE *)do_pop()) != 0)
	fclose(fp);
#else
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
#endif
