/*
    module  : user.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
user  :  X  ->  B
Tests whether X is a user-defined symbol.
*/
/* user.c */
#define PROCEDURE	user_
#define NAME		"user"
#define REL		==
#define TYP		USR_
#include "type.c"
