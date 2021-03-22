/*
    module  : case.c
    version : 1.15
    date    : 03/15/21
*/
#ifndef CASE_C
#define CASE_C

PRIVATE double Compare(pEnv env, Node *first, Node *second, int *error)
{
    char *name;

    *error = 0;
    switch (first->op) {
#ifndef OLD_RUNTIME
    case USR_:
	name = dict_descr(env, first->u.num);
	switch (second->op) {
	case USR_:
	    return strcmp(name, dict_descr(env, second->u.num));
	case ANON_FUNCT_:
	    return strcmp(name, procname(second->u.proc));
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	    break;
	case SYMBOL_:
	case STRING_:
	    return strcmp(name, second->u.str);
	case LIST_:
	case FLOAT_:
	case FILE_:
	    break;
	default:
	    return strcmp(name, dict_descr(env, second->u.num));
	}
	break;
#endif
    case ANON_FUNCT_:
	name = procname(first->u.proc);
	switch (second->op) {
#ifndef OLD_RUNTIME
	case USR_:
	    return strcmp(name, dict_descr(env, second->u.num));
#endif
	case ANON_FUNCT_:
	    return strcmp(name, procname(second->u.proc));
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	    break;
	case SYMBOL_:
	case STRING_:
	    return strcmp(name, second->u.str);
	case LIST_:
	case FLOAT_:
	case FILE_:
	    break;
	default:
#ifndef OLD_RUNTIME
	    return strcmp(name, dict_descr(env, second->u.num));
#endif
	    break;
	}
	break;
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
	switch (second->op) {
	case USR_:
	case ANON_FUNCT_:
	    break;
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	    return first->u.num - second->u.num;
	case SYMBOL_:
	case STRING_:
	    break;
	case LIST_:
	    return first->u.num - second->u.num;
	case FLOAT_:
	    return first->u.num - second->u.dbl;
	case FILE_:
	default:
	    break;
	}
	break;
    case SET_:
	switch (second->op) {
	case USR_:
	case ANON_FUNCT_:
	    break;
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	    return first->u.set - second->u.set;
	case SYMBOL_:
	case STRING_:
	case LIST_:
	case FLOAT_:
	case FILE_:
	default:
	    break;
	}
	break;
    case SYMBOL_:
    case STRING_:
	name = first->u.str;
	switch (second->op) {
#ifndef OLD_RUNTIME
	case USR_:
	    return strcmp(name, dict_descr(env, second->u.num));
#endif
	case ANON_FUNCT_:
	    return strcmp(name, procname(second->u.proc));
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	    break;
	case SYMBOL_:
	case STRING_:
	    return strcmp(name, second->u.str);
	case LIST_:
	case FLOAT_:
	case FILE_:
	    break;
	default:
#ifndef OLD_RUNTIME
	    return strcmp(name, dict_descr(env, second->u.num));
#endif
	    break;
	}
	break;
    case LIST_:
	return first->u.num - second->u.num;
	break;
    case FLOAT_:
	switch (second->op) {
	case USR_:
	case ANON_FUNCT_:
	    break;
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	    return first->u.dbl - second->u.num;
	case SET_:
	case SYMBOL_:
	case STRING_:
	case LIST_:
	    break;
	case FLOAT_:
	    return first->u.dbl - second->u.dbl;
	case FILE_:
	default:
	    break;
	}
	break;
    case FILE_:
	switch (second->op) {
	case USR_:
	case ANON_FUNCT_:
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	case SYMBOL_:
	case STRING_:
	case LIST_:
	case FLOAT_:
	    break;
	case FILE_:
	    return first->u.fil - second->u.fil;
	default:
	    break;
	}
	break;
    default:
#ifndef OLD_RUNTIME
	name = dict_descr(env, first->u.num);
	switch (second->op) {
	case USR_:
	    return strcmp(name, dict_descr(env, second->u.num));
	case ANON_FUNCT_:
	    return strcmp(name, procname(second->u.proc));
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	    break;
	case SYMBOL_:
	case STRING_:
	    return strcmp(name, second->u.str);
	case LIST_:
	case FLOAT_:
	case FILE_:
	    break;
	default:
	    return strcmp(name, dict_descr(env, second->u.num));
	}
#endif
	break;
    }
    *error = 1;
    return 0;
}

#ifndef OLD_RUNTIME
int put_case(pEnv env)
{
    Node *cur;

    if (!LIST_1)
	return 0;
    cur = env->stk->u.lis;
    POP(env->stk);
    printstack(env, outfp);
    fprintf(outfp, "{ /* CASE */");
    fprintf(outfp, "int num = 0, ok; for (;;) {");
    for (; cur->next; cur = cur->next) {
	printnode(env, cur, outfp);
	fprintf(outfp, "if (Compare(env, env->stk->u.lis, env->stk->next, &ok) == ok) {");
	fprintf(outfp, "POP(env->stk); POP(env->stk);");
	compile(env, cur->u.lis->next);
	fprintf(outfp, "num = 1; break; }");
    }
    fprintf(outfp, "break; } if (!num) {");
    fprintf(outfp, "POP(env->stk);");
    compile(env, cur->u.lis);
    fprintf(outfp, "} }");
    return 1;
}
#endif

/**
case  :  X [..[X Y]..]  ->  Y i
Indexing on the value of X, execute the matching Y.
*/
PRIVATE void do_case(pEnv env)
{
    int ok;
    Node *cur;

#ifndef OLD_RUNTIME
    if (compiling && put_case(env))
	return;
    COMPILE;
#endif
    TWOPARAMS("case");
    LIST("case");
    CHECKEMPTYLIST(env->stk->u.lis, "case");
    cur = env->stk->u.lis;
    POP(env->stk);
    for (; cur->next; cur = cur->next)
	if (Compare(env, cur->u.lis, env->stk, &ok) == ok)
	    break;
    if (cur->next) {
	POP(env->stk);
	exeterm(env, cur->u.lis->next);
    } else
	exeterm(env, cur->u.lis);
}
#endif
