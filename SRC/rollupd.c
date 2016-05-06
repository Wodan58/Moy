/*
    module  : rollupd.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
rollupd  :  X Y Z W  ->  Z X Y W
As if defined by:   rollupd  ==  [rollup] dip
*/
/* rollupd.c */
#define PROCEDURE	rollupd_
#define NAME		"rollupd"
#define PARAMCOUNT	FOURPARAMS
#define ARGUMENT	rollup_
#include "dipped.c"
