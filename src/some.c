/*
    module  : some.c
    version : 1.7
    date    : 07/15/18
*/
#ifndef SOME_X
#define SOME_C

#ifdef NEW_RUNTIME
void do_some(void)
{
    int num = 0;
    code_t *prog, *list;

    TRACE;
    prog = (code_t *)do_pop();
    for (list = (code_t *)do_pop(); list; list = list->next) {
	do_push(list->num);
	execute(prog);
	num = do_pop();
	do_pop();
	if (num)
	    break;
    }
    do_push(num);
}
#else
/**
some  :  A [B]  ->  X
Applies test B to members of aggregate A, X = true if some pass.
*/
#define PROCEDURE	do_some
#define NAME		"some"
#define INITIAL		0
#define SOME
#include "someall.h"
#undef SOME
/* some.c */
#endif
#endif
