/*
    module  : rolldownd.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
rolldownd  :  X Y Z W  ->  Y Z X W
As if defined by:   rolldownd  ==  [rolldown] dip
*/
#define PROCEDURE	do_rolldownd
#define NAME		"rolldownd"
#define PARAMCOUNT	FOURPARAMS
#define ARGUMENT	do_rolldown
#include "dipped.h"
