/*
    module  : rolldownd.c
    version : 1.5
    date    : 07/10/18
*/
#ifndef ROLLDOWND_X
#define ROLLDOWND_C

#ifndef ROLLDOWN_C
#undef ROLLDOWN_X
#include "rolldown.c"
#define ROLLDOWN_X
#endif

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
