/*
    module  : index.c
    version : 1.5
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_index(void)
{
    code_t *cur;

    TRACE;
    cur = (code_t *)do_pop();
    if (stk[-1])
	cur = cur->next;
    stk[-1] = cur->num;
}
#else
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
#endif
