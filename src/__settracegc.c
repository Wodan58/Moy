/*
    module  : __settracegc.c
    version : 1.12
    date    : 09/17/24
*/
#ifndef __SETTRACEGC_C
#define __SETTRACEGC_C

/**
Q0  OK  2970  __settracegc  :  D  I  ->
[IMPURE] Sets value of flag for tracing garbage collection to I (= 0..6).
*/
void __settracegc_(pEnv env)
{
    Node node;

    PARM(1, PREDSUCC);
    node = vec_pop(env->stck);
    if (node.u.num)		/* 0=enable compiling */
	;
    else if (env->bytecoding)
	env->bytecoding = 1;	/* LCOV_EXCL_LINE */
    else if (env->compiling)
	env->compiling = 1;	/* LCOV_EXCL_LINE */
    else
	env->ignore = 0;	/* disable ignore */
}
#endif
