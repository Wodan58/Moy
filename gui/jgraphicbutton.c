/*
    module  : 
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGRAPHICBUTTON_C
#define JGRAPHICBUTTON_C

/**
jgraphicbutton  :  obj filename  ->  event
Creates a new graphicbutton component with the image loaded from filename and
returns its event number.
*/
PRIVATE void do_jgraphicbutton(pEnv env)
{
    int obj;
    char *filename;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    STRING(__func__);
    INTEGER2(__func__);
    filename = env->stk->u.str;
    POP(env->stk);
    obj = env->stk->u.num;
    env->stk->u.num = j_graphicbutton(obj, filename);
}
#endif
