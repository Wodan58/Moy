/*
    module  : all.c
    version : 1.6
    date    : 07/10/18
*/
#ifndef ALL_X
#define ALL_C

#ifdef RUNTIME
void do_all(void)
{
    int num = 1;
    code_t *prog, *list;

    TRACE;
    prog = (code_t *)do_pop();
    for (list = (code_t *)do_pop(); list; list = list->next) {
	do_push(list->num);
	execute(prog);
	num = do_pop();
	do_pop();
	if (!num)
	    break;
    }
    do_push(num);
}
#else
/**
all  :  A [B]  ->  X
Applies test B to members of aggregate A, X = true if all pass.
*/
#define PROCEDURE	do_all
#define NAME		"all"
#define INITIAL		1
#include "someall.h"
/* all.c */
#endif
#endif
