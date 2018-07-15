/*
    module  : user.c
    version : 1.6
    date    : 07/15/18
*/
#ifndef USER_X
#define USER_C

#ifdef NEW_RUNTIME
void do_user(void)
{
    TRACE;
}
#else
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
#endif
