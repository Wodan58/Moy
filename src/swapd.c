/*
    module  : swapd.c
    version : 1.4
    date    : 07/02/18
*/

/**
swapd  :  X Y Z  ->  Y X Z
As if defined by:   swapd  ==  [swap] dip
*/
#define PROCEDURE	do_swapd
#define NAME		"swapd"
#define PARAMCOUNT	THREEPARAMS
#define ARGUMENT	do_swap
#include "dipped.h"
