/*
    module  : file.c
    version : 1.6
    date    : 07/15/18
*/
#ifndef FILE_X
#define FILE_C

#ifdef NEW_RUNTIME
void do_file(void)
{
    TRACE;
}
#else
/**
file  :  F  ->  B
Tests whether F is a file.
*/
#define PROCEDURE	do_file
#define NAME		"file"
#define REL		==
#define TYP		FILE_
#include "type.h"
#endif
#endif
