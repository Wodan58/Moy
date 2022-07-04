/*
    module  : stop.c
    version : 1.12
    date    : 06/20/22
*/
#ifndef STOP_C
#define STOP_C

#ifdef PUT_X
#undef PUT_X
#undef PUT_C
#endif

#include "put.c"

PRIVATE void do_stop(pEnv env)
{
    COMPILE;
    if (env->stk) {
	switch (autoput) {
	case 0:
	    break;
	case 1:
	    do_put(env);
	    break;
	case 2:
	    writeterm(env, env->stk);
	    break;
	}
	if (autoput)
	    putchar('\n');
    }
}
#endif
