/*
    module  : jgetimage.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETIMAGE_C
#define JGETIMAGE_C

/**
jgetimage  :  obj  ->  event
Copy the contents of component obj into an image and return its event number.
*/
PRIVATE void do_jgetimage(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_getimage(obj);
}
#endif
