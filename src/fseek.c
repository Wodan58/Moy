/*
    module  : fseek.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

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
    if (optimizing) {
	del_history(1);
	chg_history(BOOLEAN_);
    }
    COMPILE;
    THREEPARAMS("fseek");
    INTEGER("fseek");
    INTEGER2("fseek");
#endif
    whence = stk->u.num;
    POP(stk);
    pos = stk->u.num;
    POP(stk);
#ifndef NCHECK
    FILE("fseek");
#endif
    whence = fseek(stk->u.fil, pos, whence) != 0;
    PUSH(BOOLEAN_, whence);
}
