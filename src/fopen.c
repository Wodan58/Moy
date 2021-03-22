/*
    module  : fopen.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef FOPEN_C
#define FOPEN_C

/**
fopen  :  P M  ->  S
The file system object with pathname P is opened with mode M (r, w, a, etc.)
and stream object S is pushed; if the open fails, file:NULL is pushed.
*/
PRIVATE void do_fopen(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS("fopen");
    STRING("fopen");
    STRING2("fopen");
    env->stk->next->u.fil = fopen(env->stk->next->u.str, env->stk->u.str);
    env->stk->next->op = FILE_;
    POP(env->stk);
}
#endif
