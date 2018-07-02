/*
    module  : popd.c
    version : 1.4
    date    : 07/02/18
*/

/**
popd  :  Y Z  ->  Z
As if defined by:   popd  ==  [pop] dip
*/
#define PROCEDURE	do_popd
#define NAME		"popd"
#define PARAMCOUNT	TWOPARAMS
#define ARGUMENT	do_pop
#include "dipped.h"
