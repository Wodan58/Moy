/*
    module  : jloadimage.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JLOADIMAGE_C
#define JLOADIMAGE_C

/**
jloadimage  :  filename  ->  event
Loads the image from file filename and returns its event number. The file
could be of the following format: GIF, JPEG, BMP, PPM.
*/
PRIVATE void do_jloadimage(pEnv env)
{
    char *filename;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    STRING(__func__);
    filename = env->stk->u.str;
    env->stk->u.num = j_loadimage(filename);
    env->stk->op = INTEGER_;
}
#endif
