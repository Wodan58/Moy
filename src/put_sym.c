/*
    module  : put_sym.c
    version : 1.1
    date    : 04/22/19
*/
#ifndef PUT_SYM_X
#define PUT_SYM_C

#ifdef NEW_RUNTIME
void do_put_sym(void)
{
    char *ptr;
    proc_t cur;

    TRACE;
    cur = (proc_t)do_pop();
    if ((ptr = procname((proc_t)cur)) == 0)
	 printf("%s ", (char *)cur);
    else
	 printf("%s ", ptr);
}
#else
/**
put_sym  :  X  ->
Writes X to output, pops X off stack.
*/
PRIVATE void do_put_sym(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("put_sym");
    writefactor(stk, stdout);
    putchar(' ');
    POP(stk);
}
#endif
#endif
