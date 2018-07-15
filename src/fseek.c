/*
    module  : fseek.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef FSEEK_X
#define FSEEK_C

#ifdef NEW_RUNTIME
void do_fseek(void)
{
    long_t pos;
    int whence;

    TRACE;
    whence = do_pop();
    pos = do_pop();
    whence = fseek((FILE *)stk[-1], pos, whence) != 0;
    do_push(whence);
}
#else
/**
fseek  :  S P W  ->  S B
Stream S is repositioned to position P relative to whence-point W,
where W = 0, 1, 2 for beginning, current position, end respectively.
*/
PRIVATE void do_fseek(void)
{
    long_t pos;
    int whence;

#ifndef OLD_RUNTIME
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
#endif
#endif
