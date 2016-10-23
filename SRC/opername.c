/*
    module  : opername.c
    version : 1.3
    date    : 10/16/16
*/
#include "interp.h"

/* opername.c */
PUBLIC char *opername(int o)
{
    if (o >= 0 && o <= QUIT - FALSE + FALSE_)
	return optable[o].name;
    return "op_";
}
