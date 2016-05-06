/*
    module  : name.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
name  :  sym  ->  "sym"
For operators and combinators, the string "sym" is the name of item sym,
for literals sym the result string is its type.
*/
/* name.c */
PRIVATE void name_(void)
{
    char *str;

    ONEPARAM("name");
    str = stk->op == USR_ ? stk->u.ent->name : opername(stk->op);
    if (OUTSIDE) {
	stk->u.str = str;
	stk->op = STRING_;
    } else
	UNARY(STRING_NEWNODE, str);
}
