/*
    module  : user.c
    version : 1.8
    date    : 03/15/21
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
