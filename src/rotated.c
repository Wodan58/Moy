/*
    module  : rotated.c
    version : 1.7
    date    : 07/20/18
*/
#ifndef ROTATED_X
#define ROTATED_C

#ifdef RUNTIME
void do_rotated(void)
{
    node_t temp;

    TRACE;
    temp = stk[-2];
    stk[-2] = stk[-4];
    stk[-4] = temp;
}
#else
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
#endif
