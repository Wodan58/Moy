/*
    module  : fseek.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef FSEEK_C
#define FSEEK_C

/**
fseek  :  S P W  ->  S B
Stream S is repositioned to position P relative to whence-point W,
where W = 0, 1, 2 for beginning, current position, end respectively.
*/
PRIVATE void do_fseek(pEnv env)
{
    long_t pos;
    int whence;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    THREEPARAMS("fseek");
    INTEGER("fseek");
    INTEGER2("fseek");
    whence = env->stk->u.num;
    POP(env->stk);
    pos = env->stk->u.num;
    POP(env->stk);
    FILE("fseek");
    whence = fseek(env->stk->u.fil, pos, whence) != 0;
    PUSH_NUM(BOOLEAN_, whence);
}
#endif
