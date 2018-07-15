/*
    module  : _help.c
    version : 1.6
    date    : 07/15/18
*/
#ifndef _HELP_X
#define _HELP_C

#ifdef NEW_RUNTIME
void do__help(void)
{
    TRACE;
}
#else
/**
_help  :  ->
Lists all hidden symbols in library and then all hidden builtin symbols.
*/
#define PROCEDURE	do__help
#define REL		==
#include "help.h"

/* _help.c */
#endif
#endif
