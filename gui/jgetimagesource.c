/*
    module  : 
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETIMAGESOURCE_C
#define JGETIMAGESOURCE_C

Node *ArrayToList(int *ptr, int leng)
{
    int i;
    Node *root = 0, *cur;

    for (i = leng - 1; i >= 0; i--) {
	cur = GC_malloc(sizeof(Node));
	cur->u.num = ptr[i];
	cur->op = INTEGER_;
	cur->next = root;
	root = cur;
    }
    return root;
}

/**
jgetimagesource  :  obj x y w h  ->  r g b
Returns an image of the specified size (x, y, width, height) of component. The
red, green, and blue values of each picture will be stored in r, g, b.
*/
PRIVATE void do_jgetimagesource(pEnv env)
{
    int obj, x, y, w, h, *r, *g, *b;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    FIVEPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    INTEGER3(__func__);
    INTEGER4(__func__);
    INTEGER5(__func__);
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
    r = GC_malloc_atomic(w * h * sizeof(int));
    g = GC_malloc_atomic(w * h * sizeof(int));
    b = GC_malloc_atomic(w * h * sizeof(int));
    j_getimagesource(obj, x, y, w, h, r, g, b);
    PUSH_PTR(LIST_, ArrayToList(r, w * h));
    PUSH_PTR(LIST_, ArrayToList(g, w * h));
    PUSH_PTR(LIST_, ArrayToList(b, w * h));
}
#endif
