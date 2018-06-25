/*
    module  : user.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
user  :  X  ->  B
Tests whether X is a user-defined symbol.
*/
#define PROCEDURE	do_user
#define NAME		"user"
#define REL		==
#define TYP		USR_
#include "type.h"
