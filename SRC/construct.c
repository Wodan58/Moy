/*
    module  : construct.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
construct  :  [P] [[P1] [P2] ..]  ->  R1 R2 ..
Saves state of stack and then executes [P].
Then executes each [Pi] to give Ri pushed onto saved stack.
*/
/* construct.c */
PRIVATE void construct_(void)
{
    Node *cur, *test, *root, *save;

    TWOPARAMS("construct");
    TWOQUOTES("construct");
    cur = stk->u.lis;
    POP(stk);
    test = stk->u.lis;
    POP(stk);
    root = stk;
    inside_condition++;
    exeterm(test);
    for (save = stk; cur; cur = cur->next) {
	stk = save;
	exeterm(cur->u.lis);
	root = newnode(stk->op, stk->u.ptr, root);
    }
    inside_condition--;
    stk = root;
}
