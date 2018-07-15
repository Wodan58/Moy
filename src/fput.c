/*
    module  : fput.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef FPUT_X
#define FPUT_C

#ifdef NEW_RUNTIME
void do_fput(void)
{
    FILE *fp;
    node_t temp;
    int stdout_dup;

    TRACE;
    temp = do_pop();
    fp = (FILE *)stk[-1];
    stdout_dup = dup(1);
    dup2(fileno(fp), 1);
    print_node(temp);
    dup2(stdout_dup, 1);
    close(stdout_dup);
}
#else
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
#endif
