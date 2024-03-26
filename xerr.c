/*
 *  module  : xerr.c
 *  version : 1.2
 *  date    : 03/21/24
 */
#include "globals.h"

/*
    print a runtime error to stderr and abort the execution of current program.
*/
void execerror(char *filename, char *message, char *op)
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
    fprintf(stderr, "%s:run time error: %s needed for %.*s\n", filename,
	    message, leng, ptr);
    abortexecution_(ABORT_RETRY);
}
