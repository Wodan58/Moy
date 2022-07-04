/*
    module  : name.c
    version : 1.13
    date    : 06/20/22
*/
#ifndef NAME_C
#define NAME_C

/**
name  :  sym  ->  "sym"
For operators and combinators, the string "sym" is the name of item sym,
for literals sym the result string is its type.
*/
PRIVATE void do_name(pEnv env)
{
#ifdef COMPILING
    char *str = "";

    ONEPARAM("name");
    switch (env->stk->op) {
    case USR_:
	str = dict_descr(env, env->stk);
	break;
    case ANON_FUNCT_:
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
    case SET_:
    case STRING_:
    case LIST_:
    case FLOAT_:
    case FILE_:
	str = optable[env->stk->op].name;
	break;
    }
    UNARY(STRING_NEWNODE, str);
#endif
}
#endif
