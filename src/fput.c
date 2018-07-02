/*
    module  : fput.c
    version : 1.6
    date    : 07/02/18
*/

/**
fput  :  S X  ->  S
Writes X to stream S, pops X off stack.
*/
PRIVATE void do_fput(void)
{
    FILE *fp;
    Node temp;

#ifndef NCHECK
    COMPILE;
#endif
    TWOPARAMS("fput");
    if (stk->next->op != FILE_ || !stk->next->u.fil)
	execerror("file", "fput");
    temp = *stk;
    POP(stk);
    fp = stk->u.fil;
    writefactor(&temp, fp);
    putc(' ', fp);
}
