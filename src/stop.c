/*
    module  : stop.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

PRIVATE void do_stop(void)
{
    int written = 0;

#ifndef NCHECK
    if (optimizing)
	del_history(1);
    COMPILE;
#endif
    if (stk == memory)
	return;
    if (autoput == 2) {
	writeterm(stk, stdout);
	written = 1;
    } else if (autoput == 1) {
	do_put();
	written = 1;
    }
    if (written) {
	putchar('\n');
	fflush(stdout);
    }
}
