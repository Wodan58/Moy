/*
    module  : primrec.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
primrec  :  X [I] [C]  ->  R
Executes I to obtain an initial value R0.
For integer X uses increasing positive integers to X, combines by C for new R.
For aggregate X uses successive members and combines by C for new R.
*/
/* primrec.c */
PRIVATE void primrec_(void)
{
    int i, num = 0;
    Node *data, *second, *third;

    THREEPARAMS("primrec");
    third = stk->u.lis;
    POP(stk);
    second = stk->u.lis;
    POP(stk);
    data = stk;
    POP(stk);
    switch (data->op) {
    case LIST_:
	 {
	    Node *cur;
	    for (cur = data->u.lis; cur; cur = cur->next, num++)
		DUPLICATE(cur);
	    break;
	}
    case STRING_:
	 {
	    char *str;
	    for (str = data->u.str; str && *str; str++, num++)
		PUSH(CHAR_, (long_t)*str);
	    break;
	}
    case SET_:
	 {
	    long_t set = data->u.set;
	    for (i = 0; i < SETSIZE; i++)
		if (set & (1 << i)) {
		    PUSH(INTEGER_, i);
		    num++;
		}
	    break;
	}
    case INTEGER_:
	 {
	    for (i = num = data->u.num; i > 0; i--)
		PUSH(INTEGER_, i);
	    break;
	}
    default:
	BADDATA("primrec");
    }
    exeterm(second);
    for (i = 0; i < num; i++)
	exeterm(third);
}
