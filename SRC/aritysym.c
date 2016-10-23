/*
    module  : aritysym.c
    version : 1.1
    date    : 09/23/16
*/
#include "interp.h"

/* opername.c */
PUBLIC char *aritysym(int o)
{
    if (o >= 0 && o <= QUIT - FALSE + FALSE_)
	return optable[o].effect;
    return "?";
}
