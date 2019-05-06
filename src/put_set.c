/*
    module  : put_set.c
    version : 1.1
    date    : 05/06/19
*/
#ifndef PUT_SET_X
#define PUT_SET_C

#ifdef NEW_RUNTIME
void do_put_set(void)
{
    long_t set;
    unsigned i, j;

    TRACE;
    printf("{ ");
    for (set = (long_t)do_pop(), i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
	if (set & j) {
	    printf("%d ", i);
	    if ((set &= ~j) == 0)
		break;
	}
    printf("} ");
}
#else
/**
put_set  :  X  ->
Writes X to output, pops X off stack.
*/
PRIVATE void do_put_set(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("put");
    writefactor(stk, stdout);
    putchar(' ');
    POP(stk);
}
#endif
#endif
