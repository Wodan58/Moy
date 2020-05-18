/*
    module  : rolldownd.c
    version : 1.7
    date    : 03/28/20
*/
#ifndef ROLLDOWND_C
#define ROLLDOWND_C

#ifdef ROLLDOWN_X
#undef ROLLDOWN_X
#undef ROLLDOWN_C
#endif

#include "rolldown.c"

/**
rolldownd  :  X Y Z W  ->  Y Z X W
As if defined by:   rolldownd  ==  [rolldown] dip
*/
#define PROCEDURE	do_rolldownd
#define NAME		"rolldownd"
#define PARAMCOUNT	FOURPARAMS
#define ARGUMENT	do_rolldown
#include "dipped.h"
#endif
