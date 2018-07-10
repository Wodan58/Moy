/*
    module  : put_dbl.c
    version : 1.2
    date    : 07/10/18
*/
#ifndef PUT_DBL_X
#define PUT_DBL_C

#ifdef RUNTIME
void do_put_dbl(void)
{
    int i;
    float dbl;
    node_t temp;
    char buf[MAXSTR];

    TRACE;
    temp = do_pop();
    memcpy(&dbl, &temp, sizeof(float));
    sprintf(buf, "%f", dbl);
    for (i = strlen(buf) - 1; i >= 0; i--)
	if (buf[i] == '0' || buf[i] == '.')
	    buf[i] = 0;
	else
	    break;
    printf("%s ", buf);
}
#else
/**
put_dbl  :  X  ->
Writes X to output, pops X off stack.
*/
PRIVATE void do_put_dbl(void)
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
