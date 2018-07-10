/*
    module  : rotated.c
    version : 1.5
    date    : 07/10/18
*/
#ifndef ROTATED_X
#define ROTATED_C

#ifndef ROTATE_C
#undef ROTATE_X
#include "rotate.c"
#define ROTATE_X
#endif

/**
rotated  :  X Y Z W  ->  Z Y X W
As if defined by:   rotated  ==  [rotate] dip
*/
#define PROCEDURE	do_rotated
#define NAME		"rotated"
#define PARAMCOUNT	FOURPARAMS
#define ARGUMENT	do_rotate
#include "dipped.h"
#endif
