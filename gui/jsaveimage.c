/*
    module  : jsaveimage.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSAVEIMAGE_C
#define JSAVEIMAGE_C

/**
jsaveimage  :  obj filename image  ->  status
Save the components image to file filename. The specified file format can be:
J_BMP: Win32 Bitmap Format; J_PPM: Portable pixmap.
*/
PRIVATE void do_jsaveimage(pEnv env)
{
    int obj, image;
    char *filename;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    THREEPARAMS(__func__);
    INTEGER(__func__);
    STRING2(__func__);
    INTEGER2(__func__);
    image = env->stk->u.num;
    POP(env->stk);
    filename = env->stk->u.str;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    env->stk->u.num = j_saveimage(obj, filename, image);
}
#endif
