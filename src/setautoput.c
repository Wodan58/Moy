/*
    module  : setautoput.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef SETAUTOPUT_X
#define SETAUTOPUT_C

#ifdef NEW_RUNTIME
void do_setautoput(void)
{
    TRACE;
    autoput = do_pop();
}
#else
/**
setautoput  :  I  ->
Sets value of flag for automatic put to I (if I = 0, none;
if I = 1, put; if I = 2, stack).
*/
PRIVATE void do_setautoput(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("setautoput");
    NUMERICTYPE("setautoput");
    autoput = stk->u.num;
    POP(stk);
}
#endif
#endif
