/*
    module  : 
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETSCREENHEIGHT_C
#define JGETSCREENHEIGHT_C

/**
jgetscreenheight  :  ->  height
Returns the screen height in pixels. If a virtual screen is installed, the
virtual height will be returned.
*/
PRIVATE void do_jgetscreenheight(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH_NUM(INTEGER_, j_getscreenheight());
}
#endif
