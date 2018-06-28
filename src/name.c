/*
    module  : name.c
    version : 1.6
    date    : 06/28/18
*/
#include "runtime.h"

extern struct optable_t optable[];

/**
name  :  sym  ->  "sym"
For operators and combinators, the string "sym" is the name of item sym,
for literals sym the result string is its type.
*/
PRIVATE void do_name(void)
{
#ifndef NCHECK
    char *str;

    if (optimizing)
	chg_history(STRING_);
    if (optimizing && VALID(stk))
	;
    else
	COMPILE;
    ONEPARAM("name");
    switch (stk->op) {
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
    case SET_:
    case STRING_:
    case LIST_:
    case FLOAT_:
    case FILE_:
	str = optable[stk->op].name;
	break;
    default:
	str = dict_descr(stk->u.num);
	break;
    }
    if (OUTSIDE) {
	stk->u.str = str;
	stk->op = STRING_;
    } else
	UNARY(STRING_NEWNODE, str);
#endif
}
