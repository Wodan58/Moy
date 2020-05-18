/*
    module  : name.c
    version : 1.11
    date    : 03/28/20
*/
#ifndef NAME_C
#define NAME_C

/**
name  :  sym  ->  "sym"
For operators and combinators, the string "sym" is the name of item sym,
for literals sym the result string is its type.
*/
PRIVATE void do_name(void)
{
#ifndef OLD_RUNTIME
    char *str;

    if (compiling && VALID_1)
	;
    else
	COMPILE;
    ONEPARAM("name");
    switch (stk->op) {
    case USR_:
	str = dict_descr(stk->u.num);
	break;
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
    case SYMBOL_:
	str = stk->u.str;
	break;
    default:
	BADDATA("name");
	break;
    }
    stk->u.str = str;
    stk->op = STRING_;
#endif
}
#endif
