/*
    module  : fwrite.c
    version : 1.3
    date    : 09/19/16
*/
#include "interp.h"

/*
fwrite  :  S L  ->  S
A list of integers are written as bytes to the current position of stream S.
*/
/* fwrite.c */
PRIVATE void fwrite_(void)
{
    int i;
    Node *n;
    size_t length;
    unsigned char *buf;

    TWOPARAMS("fwrite");
    LIST("fwrite");
    for (n = stk->u.lis, length = 0; n; n = n->next, length++)
#ifdef RUNTIME_CHECKS
	if (n->op != INTEGER_)
	    execerror("numeric list", "fwrite");
#else
	;
#endif
    buf = malloc(length);
    for (n = stk->u.lis, i = 0; n; n = n->next, i++)
	buf[i] = n->u.num;
    POP(stk);
    FILE("fwrite");
    fwrite(buf, length, 1, stk->u.fil);
}
