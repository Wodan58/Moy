/*
    module  : stop.c
    version : 1.4
    date    : 07/02/18
*/

PRIVATE void do_stop(void)
{
    int written = 0;

#ifndef NCHECK
    COMPILE;
#endif
    if (!stk) {
	freemem();
	return;
    }
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
    if (!stk)
	freemem();
}
