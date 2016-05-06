/*
    module  : treerec.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
treerec  :  T [O] [C]  ->  ...
T is a tree. If T is a leaf, executes O. Else executes [[[O] C] treerec] C.
*/
/* treerec.c */
PRIVATE void treerecaux(void)
{
    Node *save;

    if (stk->next->op == LIST_) {
	NULLARY(LIST_NEWNODE, ANON_FUNCT_NEWNODE(treerecaux, 0));
	cons_();
	exeterm(stk->u.lis->u.lis->next);
    } else {
	save = stk;
	POP(stk);
	exeterm(save->u.lis->u.lis);
    }
}

PRIVATE void treerec_(void)
{
    THREEPARAMS("treerec");
    TWOQUOTES("treerec");
    cons_();
    treerecaux();
}
