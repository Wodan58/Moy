/*
    module  : dupd.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef DUPD_C
#define DUPD_C

#ifdef DUP_X
#undef DUP_X
#undef DUP_C
#endif

#include "dup.c"

/**
dupd  :  Y Z  ->  Y Y Z
As if defined by:   dupd  ==  [dup] dip
*/
#define PROCEDURE	do_dupd
#define NAME		"dupd"
#define PARAMCOUNT	TWOPARAMS
#define ARGUMENT	do_dup
#include "dipped.h"
#endif
