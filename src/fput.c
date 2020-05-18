/*
    module  : fput.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef FPUT_C
#define FPUT_C

/**
fput  :  S X  ->  S
Writes X to stream S, pops X off stack.
*/
PRIVATE void do_fput(void)
{
    FILE *fp;
    Node temp;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS("fput");
#ifndef NCHECK
    if (stk->next->op != FILE_ || !stk->next->u.fil)
	execerror("file", "fput");
#endif
    temp = *stk;
    POP(stk);
    fp = stk->u.fil;
    writefactor(&temp, fp);
    putc(' ', fp);
}
#endif
