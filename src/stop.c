/*
    module  : stop.c
    version : 1.10
    date    : 03/28/20
*/
#ifndef STOP_C
#define STOP_C

#ifdef PUT_X
#undef PUT_X
#undef PUT_C
#endif

#include "put.c"

PRIVATE void do_stop(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    if (stk) {
	switch (autoput) {
	case 0:
	    break;
	case 1:
	    do_put();
	    break;
	case 2:
	    writeterm(stk, stdout);
	    break;
	}
	if (autoput)
	    putchar('\n');
    }
    if (!stk)
	freemem();
}
#endif
