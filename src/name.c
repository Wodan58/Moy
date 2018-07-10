/*
    module  : name.c
    version : 1.9
    date    : 07/10/18
*/
#ifndef NAME_X
#define NAME_C

#ifdef RUNTIME
void do_name(void)
{
}
#else
/**
name  :  sym  ->  "sym"
For operators and combinators, the string "sym" is the name of item sym,
for literals sym the result string is its type.
*/
PRIVATE void do_name(void)
{
#ifndef NCHECK
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
    if (OUTSIDE) {
	stk->u.str = str;
	stk->op = STRING_;
    } else
	UNARY(STRING_NEWNODE, str);
#endif
}
#endif
#endif
