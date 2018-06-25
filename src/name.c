/*
    module  : name.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

/**
name  :  sym  ->  "sym"
For operators and combinators, the string "sym" is the name of item sym,
for literals sym the result string is its type.
*/
PRIVATE void do_name(void)
{
    char *str;

#ifndef NCHECK
    if (optimizing)
	chg_history(STRING_);
    if (optimizing && VALID(stk))
	;
    else
	COMPILE;
    ONEPARAM("name");
#endif
    str = stk->op == USR_ ? stk->u.ent->name : opername(stk->op);
    if (OUTSIDE) {
	stk->u.str = str;
	stk->op = STRING_;
    } else
	UNARY(STRING_NEWNODE, str);
}
