/*
    module  : rollupd.c
    version : 1.10
    date    : 06/20/22
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
/* rollupd.c */
#endif
