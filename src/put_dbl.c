/*
    module  : put_dbl.c
    version : 1.3
    date    : 07/15/18
*/
#ifndef PUT_DBL_X
#define PUT_DBL_C

#ifdef NEW_RUNTIME
void do_put_dbl(void)
{
    float dbl;
    node_t temp;

    TRACE;
    temp = do_pop();
    memcpy(&dbl, &temp, sizeof(float));
    printf("%g ", dbl);
}
#else
/**
put_dbl  :  X  ->
Writes X to output, pops X off stack.
*/
PRIVATE void do_put_dbl(void)
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
