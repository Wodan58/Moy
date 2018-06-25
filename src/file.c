/*
    module  : file.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
file  :  F  ->  B
Tests whether F is a file.
*/
#define PROCEDURE	do_file
#define NAME		"file"
#define REL		==
#define TYP		FILE_
#include "type.h"
