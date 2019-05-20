/*
    module  : stop.c
    version : 1.9
    date    : 05/18/19
*/
#ifndef STOP_X
#define STOP_C

#ifdef NEW_RUNTIME

#ifndef POP_C
#undef POP_X
#include "pop.c"
#define POP_X
#endif

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
#ifdef VECTOR
    if (vec_empty(theStack))
#else
    if (stk == memory)
#endif
	freemem();
}
#else

#ifndef PUT_C
#undef PUT_X
#include "put.c"
#define PUT_X
#endif

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
#endif
