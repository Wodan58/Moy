/*
    module  : dupd.c
    version : 1.4
    date    : 07/02/18
*/

/**
dupd  :  Y Z  ->  Y Y Z
As if defined by:   dupd  ==  [dup] dip
*/
#define PROCEDURE	do_dupd
#define NAME		"dupd"
#define PARAMCOUNT	TWOPARAMS
#define ARGUMENT	do_dup
#include "dipped.h"
