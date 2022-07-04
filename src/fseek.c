/*
    module  : fseek.c
    version : 1.11
    date    : 06/20/22
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
    long pos;
    int whence;

    COMPILE;
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
