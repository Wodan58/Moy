/*
    module  : user.c
    version : 1.7
    date    : 03/28/20
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
#define TYP		USR_
#include "type.h"
#endif
