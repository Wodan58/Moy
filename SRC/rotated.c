/*
    module  : rotated.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
rotated  :  X Y Z W  ->  Z Y X W
As if defined by:   rotated  ==  [rotate] dip
*/
/* rotated.c */
#define PROCEDURE	rotated_
#define NAME		"rotated"
#define PARAMCOUNT	FOURPARAMS
#define ARGUMENT	rotate_
#include "dipped.c"
