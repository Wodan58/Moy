/*
    module  : opername.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/* opername.c */
PUBLIC char *opername(int o)
{
    return optable[o].name;
}
