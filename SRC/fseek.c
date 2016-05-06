/*
    module  : fseek.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
fseek  :  S P W  ->  S B
Stream S is repositioned to position P relative to whence-point W,
where W = 0, 1, 2 for beginning, current position, end respectively.
*/
/* fseek.c */
PRIVATE void fseek_(void)
{
    long_t pos;
    int whence;

    THREEPARAMS("fseek");
    INTEGER("fseek");
    INTEGER2("fseek");
    whence = stk->u.num;
    POP(stk);
    pos = stk->u.num;
    POP(stk);
    FILE("fseek");
    PUSH(BOOLEAN_, fseek(stk->u.fil, pos, whence) != 0);
}
