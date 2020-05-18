/*
    module  : index.c
    version : 1.8
    date    : 03/28/20
*/
#ifndef INDEX_C
#define INDEX_C

/**
index  :  I A  ->  X
X (= A[I]) is the member of A at position I (I = 0,1).
*/
PRIVATE void do_index(void)
{
    Node *list;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS("index");
    list = stk->u.lis;
    if (stk->next->u.num)
	list = list->next;
    POP(stk);
    stk->op = list->op;
    stk->u = list->u;
}
#endif
