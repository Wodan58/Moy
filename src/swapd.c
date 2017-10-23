/*
    module  : swapd.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
swapd  :  X Y Z  ->  Y X Z
As if defined by:   swapd  ==  [swap] dip
*/
#define PROCEDURE	do_swapd
#define NAME		"swapd"
#define PARAMCOUNT	THREEPARAMS
#define ARGUMENT	do_swap
#include "dipped.c"
