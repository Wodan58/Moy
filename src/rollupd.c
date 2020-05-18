/*
    module  : rollupd.c
    version : 1.8
    date    : 03/28/20
*/
#ifndef ROLLUPD_C
#define ROLLUPD_C

#ifdef ROLLUP_X
#undef ROLLUP_X
#undef ROLLUP_C
#endif

#include "rollup.c"

/**
rollupd  :  X Y Z W  ->  Z X Y W
As if defined by:   rollupd  ==  [rollup] dip
*/
#define PROCEDURE	do_rollupd
#define NAME		"rollupd"
#define PARAMCOUNT	FOURPARAMS
#define ARGUMENT	do_rollup
#include "dipped.h"
#endif
