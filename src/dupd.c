/*
    module  : dupd.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
dupd  :  Y Z  ->  Y Y Z
As if defined by:   dupd  ==  [dup] dip
*/
#define PROCEDURE	do_dupd
#define NAME		"dupd"
#define PARAMCOUNT	TWOPARAMS
#define ARGUMENT	do_dup
#include "dipped.c"
