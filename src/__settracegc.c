/*
    module  : __settracegc.c
    version : 1.9
    date    : 02/09/24
*/
#ifndef __SETTRACEGC_C
#define __SETTRACEGC_C

/**
OK 2970  __settracegc  :  D	I  ->
[IMPURE] Sets value of flag for tracing garbage collection to I (= 0..6).
*/
void __settracegc_(pEnv env)
{
    Node node;

    PARM(1, PREDSUCC);
    env->stck = pvec_pop(env->stck, &node);
    if (node.u.num) {			/* enable compiling */
	if (env->bytecoding)
	    env->bytecoding = 1;
	else if (env->compiling)
	    env->compiling = 1;
    }
}
#endif
