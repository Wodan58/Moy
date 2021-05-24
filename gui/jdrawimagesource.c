/*
    module  : 
    version : 1.1
    date    : 04/28/21
*/
#ifndef JDRAWIMAGESOURCE_C
#define JDRAWIMAGESOURCE_C

int ListLeng(Node *cur)
{
    int leng;

    for (leng = 0; cur; cur = cur->next)
	leng++;
    return leng;
}

int *ListToArray(Node *cur)
{
    int *ptr;
    int i, leng;

    leng = ListLeng(cur);
    ptr = GC_malloc_atomic(leng * sizeof(int));
    for (i = 0; cur; cur = cur->next)
	ptr[i++] = cur->u.num;
    return ptr;
}

/**
jdrawimagesource  :  obj x y w h r g b  ->
Paints an image at Position (x, y), with width and height. The red, green, and
blue values of each pixel are given by the arrays r, g, b.
*/
PRIVATE void do_jdrawimagesource(pEnv env)
{
    int obj, x, y, w, h, *r, *g, *b;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    EIGHTPARAMS(__func__);
    LIST(__func__);
    LIST2(__func__);
    LIST3(__func__);
    INTEGER4(__func__);
    INTEGER5(__func__);
    INTEGER6(__func__);
    INTEGER7(__func__);
    INTEGER8(__func__);
    b = ListToArray(env->stk->u.lis);
    POP(env->stk);
    g = ListToArray(env->stk->u.lis);
    POP(env->stk);
    r = ListToArray(env->stk->u.lis);
    POP(env->stk);
    h = env->stk->u.num;
    POP(env->stk);
    w = env->stk->u.num;
    POP(env->stk);
    y = env->stk->u.num;
    POP(env->stk);
    x = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_drawimagesource(obj, x, y, w, h, r, g, b);
}
#endif
