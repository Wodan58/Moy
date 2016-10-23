/*
    module  : fgets.c
    version : 1.3
    date    : 09/19/16
*/
#include "interp.h"

/*
fgets  :  S  ->  S L
L is the next available line (as a string) from stream S.
*/
/* fgets.c */
PRIVATE void fgets_(void)
{
    int length = 0;
    int size = INPLINEMAX;
    char *buf = 0;

    ONEPARAM("fgets");
    FILE("fgets");
    buf = malloc(size);
    buf[0] = 0;
    while (fgets(buf + length, size - length, stk->u.fil)) {
	if ((length = strlen(buf)) > 0 && buf[length - 1] == '\n')
	    break;
	buf = realloc(buf, size <<= 1);
    }
    PUSH(STRING_, buf);
}
