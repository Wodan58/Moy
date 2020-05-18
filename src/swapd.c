/*
    module  : swapd.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef SWAPD_C
#define SWAPD_C

#ifdef SWAP_X
#undef SWAP_X
#undef SWAP_C
#endif

#include "swap.c"

/**
swapd  :  X Y Z  ->  Y X Z
As if defined by:   swapd  ==  [swap] dip
*/
#define PROCEDURE	do_swapd
#define NAME		"swapd"
#define PARAMCOUNT	THREEPARAMS
#define ARGUMENT	do_swap
#include "dipped.h"
#endif
