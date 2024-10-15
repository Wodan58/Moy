/*
 *  module  : xerr.c
 *  version : 1.5
 *  date    : 10/11/24
 */
#include "globals.h"

/*
    print a runtime error to stderr and abort the execution of current program.
*/
void execerror(char *message, char *op)
{
    int leng = 0;
    char *ptr, *str;

    if ((ptr = strrchr(op, '/')) != 0)
	ptr++;
    else
	ptr = op;
    if ((str = strrchr(ptr, '.')) != 0 && str[1] == 'c')
	leng = str - ptr;
    else
	leng = strlen(ptr);
    fflush(stdout);
    fprintf(stderr, "\nrun time error: %s needed for %.*s\n", message, leng,
	    ptr);
    abortexecution_(ABORT_ERROR);
}	/* LCOV_EXCL_LINE */
