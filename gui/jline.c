/*
    module  : jline.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JLINE_C
#define JLINE_C

/**
jline  :  obj orient style length  ->  event
Creates a new line component with the specified length and returns its event
number. A line may be used to separate groups of components. On error -1 will
be returned. The parameter orient specifies the orientation of the line:
J_HORIZONTAL: horizontal line; J_VERTICAL: vertical line. The parameter style
specifies the line style: J_LINEDOWN: etched-in line style; J_LINEUP:
etched-out line style.
*/
PRIVATE void do_jline(pEnv env)
{
    int obj, orient, style, length;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    FOURPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    INTEGER3(__func__);
    INTEGER4(__func__);
    length = env->stk->u.num;
    POP(env->stk);
    style = env->stk->u.num;
    POP(env->stk);
    orient = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    env->stk->u.num = j_line(obj, orient, style, length);
}
#endif
