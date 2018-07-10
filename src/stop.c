/*
    module  : stop.c
    version : 1.7
    date    : 07/10/18
*/
#ifndef STOP_X
#define STOP_C

#ifndef POP_C
#undef POP_X
#include "pop.c"
#define POP_X
#endif

#ifdef RUNTIME
void do_stop(void)
{
    TRACE;
#ifdef VECTOR
    if (autoput && !vec_empty(theStack)) {
#else
    if (autoput && stk > memory) {
#endif
	print_node(do_pop());
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
#endif
