/*
    module  : index.c
    version : 1.10
    date    : 06/20/22
*/
#ifndef INDEX_C
#define INDEX_C

/**
index  :  I A  ->  X
X (= A[I]) is the member of A at position I (I = 0,1).
*/
PRIVATE void do_index(pEnv env)
{
    Node *cur;

    COMPILE;
    TWOPARAMS("index");
    cur = env->stk->u.lis;
    if (env->stk->next->u.num)
	cur = cur->next;
    GBINARY(cur->op, cur->u);
}
#endif
