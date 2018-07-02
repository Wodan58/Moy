/*
    module  : fseek.c
    version : 1.6
    date    : 07/02/18
*/

/**
fseek  :  S P W  ->  S B
Stream S is repositioned to position P relative to whence-point W,
where W = 0, 1, 2 for beginning, current position, end respectively.
*/
PRIVATE void do_fseek(void)
{
    long_t pos;
    int whence;

#ifndef NCHECK
    COMPILE;
#endif
    THREEPARAMS("fseek");
    INTEGER("fseek");
    INTEGER2("fseek");
    whence = stk->u.num;
    POP(stk);
    pos = stk->u.num;
    POP(stk);
    FILE("fseek");
    whence = fseek(stk->u.fil, pos, whence) != 0;
    PUSH(BOOLEAN_, whence);
}
