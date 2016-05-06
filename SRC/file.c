/*
    module  : file.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
file  :  F  ->  B
Tests whether F is a file.
*/
/* file.c */
#define PROCEDURE	file_
#define NAME		"file"
#define REL		==
#define TYP		FILE_
#include "type.c"
