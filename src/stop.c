/*
    module  : stop.c
    version : 1.11
    date    : 03/15/21
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
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    if (env->stk) {
	switch (autoput) {
	case 0:
	    break;
	case 1:
	    do_put(env);
	    break;
	case 2:
	    writeterm(env, env->stk, stdout);
	    break;
	}
	if (autoput)
	    putchar('\n');
    }
}
#endif
