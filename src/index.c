/*
    module  : index.c
    version : 1.4
    date    : 07/02/18
*/

/**
index  :  I A  ->  X
X (= A[I]) is the member of A at position I (I = 0,1).
*/
PRIVATE void do_index(void)
{
    Node *list;

#ifndef NCHECK
    COMPILE;
#endif
    TWOPARAMS("index");
    list = stk->u.lis;
    if (stk->next->u.num)
	list = list->next;
    if (OUTSIDE) {
	POP(stk);
	stk->op = list->op;
	stk->u = list->u;
    } else
	GBINARY(list->op, list->u.ptr);
}
