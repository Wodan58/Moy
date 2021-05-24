/*
    module  : 
    version : 1.1
    date    : 04/28/21
*/
#ifndef JPLAYSOUNDFILE_C
#define JPLAYSOUNDFILE_C

/**
jplaysoundfile  :  filename  ->
Play a sound file.
*/
PRIVATE void do_jplaysoundfile(pEnv env)
{
    char *filename;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    STRING(__func__);
    filename = env->stk->u.str;
    POP(env->stk);
    j_playsoundfile(filename);
}
#endif
