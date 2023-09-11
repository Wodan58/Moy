/*
    module  : manual.c
    version : 1.3
    date    : 09/11/23
*/
#ifndef MANUAL_C
#define MANUAL_C

#include "manual.h"

/**
OK 2930  manual  :  N	->
Writes this manual of all Joy primitives to output file.
*/
void manual_(pEnv env)
{
#ifndef COMPILER
#ifndef RUNTIME
    make_manual(0);
#endif
#endif
}
#endif
