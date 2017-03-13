/*
    module  : popd.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
popd  :  Y Z  ->  Z
As if defined by:   popd  ==  [pop] dip
*/
#define PROCEDURE	do_popd
#define NAME		"popd"
#define PARAMCOUNT	TWOPARAMS
#define ARGUMENT	do_pop
#include "dipped.c"
