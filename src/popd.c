/*
    module  : popd.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef POPD_C
#define POPD_C

#ifdef POP_X
#undef POP_X
#undef POP_C
#endif

#include "pop.c"

/**
popd  :  Y Z  ->  Z
As if defined by:   popd  ==  [pop] dip
*/
#define PROCEDURE	do_popd
#define NAME		"popd"
#define PARAMCOUNT	TWOPARAMS
#define ARGUMENT	do_pop
#include "dipped.h"
/* popd.c */
#endif
