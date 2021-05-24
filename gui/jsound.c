/*
    module  : jsound.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSOUND_C
#define JSOUND_C

/**
jsound  :  sound  ->
Play a sound.
*/
PRIVATE void do_jsound(pEnv env)
{
    char *sound;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    STRING(__func__);
    sound = env->stk->u.str;
    POP(env->stk);
    j_sound(sound);
}
#endif
