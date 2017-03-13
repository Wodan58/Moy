/*
    module  : file.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
file  :  F  ->  B
Tests whether F is a file.
*/
#define PROCEDURE	do_file
#define NAME		"file"
#define REL		==
#define TYP		FILE_
#include "type.c"
