/*
    module  : index.c
    version : 1.9
    date    : 03/15/21
*/
#ifndef INDEX_C
#define INDEX_C

/**
index  :  I A  ->  X
X (= A[I]) is the member of A at position I (I = 0,1).
*/
PRIVATE void do_index(pEnv env)
{
    Node *list;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS("index");
    list = env->stk->u.lis;
    if (env->stk->next->u.num)
	list = list->next;
    POP(env->stk);
    env->stk->op = list->op;
    env->stk->u = list->u;
}
#endif
