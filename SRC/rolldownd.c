/*
    module  : rolldownd.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
rolldownd  :  X Y Z W  ->  Y Z X W
As if defined by:   rolldownd  ==  [rolldown] dip
*/
/* rolldownd.c */
#define PROCEDURE	rolldownd_
#define NAME		"rolldownd"
#define PARAMCOUNT	FOURPARAMS
#define ARGUMENT	rolldown_
#include "dipped.c"
