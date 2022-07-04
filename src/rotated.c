/*
    module  : rotated.c
    version : 1.10
    date    : 06/20/22
*/
#ifndef ROTATED_X
#define ROTATED_C

#ifdef ROTATE_X
#undef ROTATE_X
#undef ROTATE_C
#endif

#include "rotate.c"

/**
rotated  :  X Y Z W  ->  Z Y X W
As if defined by:   rotated  ==  [rotate] dip
*/
#define PROCEDURE	do_rotated
#define NAME		"rotated"
#define PARAMCOUNT	FOURPARAMS
#define ARGUMENT	do_rotate
#include "dipped.h"
/* rotated.c */
#endif
