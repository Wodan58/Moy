/*
    module  : popd.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
popd  :  Y Z  ->  Z
As if defined by:   popd  ==  [pop] dip
*/
/* popd.c */
#define PROCEDURE	popd_
#define NAME		"popd"
#define PARAMCOUNT	TWOPARAMS
#define ARGUMENT	pop_
#include "dipped.c"
