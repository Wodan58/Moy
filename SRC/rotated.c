/*
    module  : rotated.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
rotated  :  X Y Z W  ->  Z Y X W
As if defined by:   rotated  ==  [rotate] dip
*/
#define PROCEDURE	do_rotated
#define NAME		"rotated"
#define PARAMCOUNT	FOURPARAMS
#define ARGUMENT	do_rotate
#include "dipped.c"
