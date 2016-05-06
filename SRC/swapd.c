/*
    module  : swapd.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
swapd  :  X Y Z  ->  Y X Z
As if defined by:   swapd  ==  [swap] dip
*/
/* swapd.c */
#define PROCEDURE	swapd_
#define NAME		"swapd"
#define PARAMCOUNT	THREEPARAMS
#define ARGUMENT	swap_
#include "dipped.c"
