/*
    module  : 
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETSCREENWIDTH_C
#define JGETSCREENWIDTH_C

/**
jgetscreenwidth  :  ->  width
Returns the screen width in pixels. If a virtual screen is installed, the
virtual width will be returned.
*/
PRIVATE void do_jgetscreenwidth(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH_NUM(INTEGER_, j_getscreenwidth());
}
#endif
