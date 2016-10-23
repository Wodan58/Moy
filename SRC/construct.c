/*
    module  : construct.c
    version : 1.5
    date    : 10/04/16
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
    Node *cur, *prog, *root = 0, *save[2];

    TWOPARAMS("construct");
    TWOQUOTES("construct");
    cur = stk->u.lis;
    POP(stk);
    prog = stk->u.lis;
    POP(stk);
    save[0] = stk;
    exeterm(prog);
    for ( ; cur; cur = cur->next) {
	save[1] = stk;
#ifdef ARITY
	copy_(arity(cur->u.lis));
#else
	CONDITION;
#endif
	exeterm(cur->u.lis);
	root = heapnode(stk->op, stk->u.ptr, root);
	stk = save[1];
#ifndef ARITY
	RELEASE;
#endif
    }
    stk = save[0];
    for (cur = root; cur; cur = cur->next)
	DUPLICATE(cur);
}
