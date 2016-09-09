/*
    module  : step.c
    version : 1.3
    date    : 09/09/16
*/
#include "interp.h"

/*
step  :  A [P]  ->  ...
Sequentially putting members of aggregate A onto stack,
executes P for each member of A.
*/
/* step.c */
PRIVATE void step_(void)
{
    Node *prog, *data, *cur;

    TWOPARAMS("step");
    ONEQUOTE("step");
    prog = stk->u.lis;
    POP(stk);
    data = stk;
    POP(stk);
    switch (data->op) {
    case LIST_:
	 {
	    for (cur = data->u.lis; cur; cur = cur->next) {
		DUPLICATE(cur);
		exeterm(prog);
	    }
	    break;
	}
    case STRING_:
	 {
	    char *str;
	    for (str = data->u.str; str && *str; str++) {
		PUSH(CHAR_, (long_t)*str);
		exeterm(prog);
	    }
	    break;
	}
    case SET_:
	 {
	    int i;
	    long_t set = data->u.set;
	    for (i = 0; i < _SETSIZE_; i++)
		if (set & (1 << i)) {
		    PUSH(INTEGER_, i);
		    exeterm(prog);
		}
	    break;
	}
    default:
	BADAGGREGATE("step");
    }
}
