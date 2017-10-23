/*
    module  : user.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
user  :  X  ->  B
Tests whether X is a user-defined symbol.
*/
#define PROCEDURE	do_user
#define NAME		"user"
#define REL		==
#define TYP		USR_
#include "type.c"
