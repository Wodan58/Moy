/*
    module  : rollupd.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
rollupd  :  X Y Z W  ->  Z X Y W
As if defined by:   rollupd  ==  [rollup] dip
*/
#define PROCEDURE	do_rollupd
#define NAME		"rollupd"
#define PARAMCOUNT	FOURPARAMS
#define ARGUMENT	do_rollup
#include "dipped.c"
