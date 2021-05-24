/*
    module  : jgetitem.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETITEM_C
#define JGETITEM_C

/**
jgetitem  :  obj item  ->  label
Returns the label of the given item.
*/
PRIVATE void do_jgetitem(pEnv env)
{
    int obj, item;
    char label[MAXSTR];

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    item = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    j_getitem(obj, item, label);
    env->stk->u.str = GC_strdup(label);
    env->stk->op = STRING_;
}
#endif
