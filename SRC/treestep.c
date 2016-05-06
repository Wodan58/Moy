/*
    module  : treestep.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
treestep  :  T [P]  ->  ...
Recursively traverses leaves of tree T, executes P for each leaf.
*/
/* treestep.c */
PRIVATE void treestepaux(Node *item, Node *prog)
{
    Node *cur;

    if (item->op != LIST_) {
	DUPLICATE(item);
	exeterm(prog);
    } else for (cur = item->u.lis; cur; cur = cur->next)
	treestepaux(cur, prog);
}

PRIVATE void treestep_(void)
{
    Node *item, *prog;

    TWOPARAMS("treestep");
    ONEQUOTE("treestep");
    prog = stk->u.lis;
    POP(stk);
    item = stk;
    POP(stk);
    treestepaux(item, prog);
}
