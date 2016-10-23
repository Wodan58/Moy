/*
    module  : primrec.c
    version : 1.4
    date    : 10/16/16
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
    char *str;
    long_t set;
    int i, num = 0;
    Node *cur, *init, *prog;

    THREEPARAMS("primrec");
    prog = stk->u.lis;
    POP(stk);
    init = stk->u.lis;
    POP(stk);
    cur = stk;
    POP(stk);
    switch (cur->op) {
    case LIST_:
	for (cur = cur->u.lis; cur; cur = cur->next, num++)
	    DUPLICATE(cur);
	break;
    case STRING_:
	for (str = cur->u.str; str && *str; str++, num++)
	    PUSH(CHAR_, (long_t)*str);
	break;
    case SET_:
	set = cur->u.set;
	for (i = 0; i < _SETSIZE_; i++)
	    if (set & (1 << i)) {
		PUSH(INTEGER_, i);
		num++;
	    }
	break;
    case INTEGER_:
	i = num = cur->u.num;
	while (i--)
	    PUSH(INTEGER_, i);
	break;
    default:
	BADDATA("primrec");
    }
    exeterm(init);
    while (num--)
	exeterm(prog);
}
