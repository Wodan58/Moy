/*
    module  : treegenrec.c
    version : 1.3
    date    : 10/16/16
*/
#include "interp.h"

/*
treegenrec  :  T [[O1] [O2] C]  ->  ...
T is a tree. If T is a leaf, executes O1.
Else executes O2 and then [[[O1] [O2] C] treegenrec] C.
*/
/* treegenrec.c */
PRIVATE void treegenrecaux(void)
{
    Node *save;

    save = stk;
    POP(stk);
    if (stk->op == LIST_) {
	exeterm(save->u.lis->next->u.lis);
	DUPLICATE(save);
	NULLARY(LIST_NEWNODE, ANON_FUNCT_NEWNODE(treegenrecaux, 0));
	cons_();
	exeterm(stk->u.lis->u.lis->next->next);
    } else
	exeterm(save->u.lis->u.lis);
}

PRIVATE void treegenrec_(void)
{
    FOURPARAMS("treegenrec");
    THREEQUOTES("treegenrec");
    cons_();
    cons_();
    treegenrecaux();
}
