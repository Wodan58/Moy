/*
    module  : put_str.c
    version : 1.2
    date    : 07/10/18
*/
#ifndef PUT_STR_X
#define PUT_STR_C

#ifdef RUNTIME
void do_put_str(void)
{
    char *str;

    TRACE;
    if ((str = (char *)do_pop()) == 0)
	printf("\"\" ");
    else
	printf("\"%s\" ", str);
}
#else
/**
put_str  :  X  ->
Writes X to output, pops X off stack.
*/
PRIVATE void do_put_str(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    ONEPARAM("put");
    writefactor(stk, stdout);
    putchar(' ');
    POP(stk);
}
#endif
#endif
