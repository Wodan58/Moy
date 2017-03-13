/*
    module  : rolldownd.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
rolldownd  :  X Y Z W  ->  Y Z X W
As if defined by:   rolldownd  ==  [rolldown] dip
*/
#define PROCEDURE	do_rolldownd
#define NAME		"rolldownd"
#define PARAMCOUNT	FOURPARAMS
#define ARGUMENT	do_rolldown
#include "dipped.c"
