/*
    module  : user.c
    version : 1.9
    date    : 06/20/22
*/
#ifndef USER_C
#define USER_C

/**
user  :  X  ->  B
Tests whether X is a user-defined symbol.
*/
#define PROCEDURE	do_user
#define NAME		"user"
#define REL		==
#define TYP		USR_ && env->stk->u.num >= env->firstlibra
#include "type.h"
/* user.c */
#endif
