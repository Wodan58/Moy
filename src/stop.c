/*
    module  : stop.c
    version : 1.6
    date    : 07/08/18
*/
#ifdef RUNTIME
void do_stop(void)
{
    TRACE;
    if (autoput && stk > memory) {
	do_put();
	putchar('\n');
    }
}
#else
PRIVATE void do_stop(void)
{
#ifndef NCHECK
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
