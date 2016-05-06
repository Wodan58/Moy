/*
    module  : dupd.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
dupd  :  Y Z  ->  Y Y Z
As if defined by:   dupd  ==  [dup] dip
*/
/* dupd.c */
#define PROCEDURE	dupd_
#define NAME		"dupd"
#define PARAMCOUNT	TWOPARAMS
#define ARGUMENT	dup_
#include "dipped.c"
