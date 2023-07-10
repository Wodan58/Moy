/*
    module  : __html_manual.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef __HTML_MANUAL_C
#define __HTML_MANUAL_C

/**
OK 2960  __html_manual  :  N	->
Writes this manual of all Joy primitives to output file in HTML style.
*/
void __html_manual_(pEnv env)
{
    make_manual(1);
    env->nothing++;
}
#endif
