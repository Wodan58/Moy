/*
    module  : fopen.c
    version : 1.7
    date    : 07/10/18
*/
#ifndef FOPEN_X
#define FOPEN_C

/**
fopen  :  P M  ->  S
The file system object with pathname P is opened with mode M (r, w, a, etc.)
and stream object S is pushed; if the open fails, file:NULL is pushed.
*/
PRIVATE void do_fopen(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    TWOPARAMS("fopen");
    STRING("fopen");
    STRING2("fopen");
    if (OUTSIDE) {
	stk->next->u.fil = fopen(stk->next->u.str, stk->u.str);
	stk->next->op = FILE_;
	POP(stk);
    } else
	BINARY(FILE_NEWNODE, fopen(stk->next->u.str, stk->u.str));
}
#endif
