/*
    module  : while.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
while  :  [B] [D]  ->  ...
While executing B yields true executes D.
*/
/* while.c */
PRIVATE void while_(void)
{
    int num;
    Node *body, *test, *save;

    TWOPARAMS("while");
    TWOQUOTES("while");
    body = stk->u.lis;
    POP(stk);
    test = stk->u.lis;
    POP(stk);
    for (;;) {
	save = stk;
	CONDITION;
	exeterm(test);
	num = stk->u.num;
	RELEASE;
	stk = save;
	if (!num)
	    return;
	exeterm(body);
    }
}
