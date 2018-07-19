/*
    module  : case.c
    version : 1.13
    date    : 07/19/18
*/
#ifndef CASE_X
#define CASE_C

#ifndef NEW_RUNTIME
PRIVATE double Compare(Node *first, Node *second, int *error)
{
    char *name;

    *error = 0;
    switch (first->op) {
#ifndef OLD_RUNTIME
    case USR_:
	name = dict_descr(first->u.num);
	switch (second->op) {
	case USR_:
	    return strcmp(name, dict_descr(second->u.num));
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
	    return strcmp(name, dict_descr(second->u.num));
	}
	break;
#endif
    case ANON_FUNCT_:
	name = procname(first->u.proc);
	switch (second->op) {
#ifndef OLD_RUNTIME
	case USR_:
	    return strcmp(name, dict_descr(second->u.num));
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
	    return strcmp(name, dict_descr(second->u.num));
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
	    return strcmp(name, dict_descr(second->u.num));
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
	    return strcmp(name, dict_descr(second->u.num));
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
	name = dict_descr(first->u.num);
	switch (second->op) {
	case USR_:
	    return strcmp(name, dict_descr(second->u.num));
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
	    return strcmp(name, dict_descr(second->u.num));
	}
#endif
	break;
    }
    *error = 1;
    return 0;
}
#endif

#ifdef NEW_RUNTIME
void do_case(void)
{
    code_t *cur;

    TRACE;
    for (cur = (code_t *)do_pop(); cur->next; cur = cur->next)
	if (cur->list->num == stk[-1])
	    break;
    if (cur->next) {
	(void)do_pop();
	execute(cur->list->next);
    } else
	execute(cur->list);
}
#else

#ifndef OLD_RUNTIME
int put_case(void)
{
    Node *cur;

    if (!LIST_1)
	return 0;
    cur = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* CASE */");
    if (new_version)
	fprintf(outfp, "int num = 0; for (;;) {");
    else
	fprintf(outfp, "int num = 0, ok; for (;;) {");
    for (; cur->next; cur = cur->next) {
	PrintHead(cur, outfp);
	if (new_version)
	    fprintf(outfp, "if (stk[-1] == stk[-2]) { do_pop(); do_pop();");
	else {
	    fprintf(outfp, "if (Compare(stk->u.lis, stk->next, &ok) == ok) {");
	    fprintf(outfp, "POP(stk); POP(stk);");
	}
	compile(cur->u.lis->next);
	fprintf(outfp, "num = 1; break; }");
    }
    fprintf(outfp, "break; } if (!num) {");
    if (new_version)
	fprintf(outfp, "do_pop();");
    else
	fprintf(outfp, "POP(stk);");
    compile(cur->u.lis);
    fprintf(outfp, "} }");
    return 1;
}
#endif

/**
case  :  X [..[X Y]..]  ->  Y i
Indexing on the value of X, execute the matching Y.
*/
PRIVATE void do_case(void)
{
    int ok;
    Node *cur;

#ifndef OLD_RUNTIME
    if (compiling && put_case())
	return;
    COMPILE;
#endif
    TWOPARAMS("case");
    LIST("case");
    CHECKEMPTYLIST(stk->u.lis, "case");
    cur = stk->u.lis;
    POP(stk);
    for (; cur->next; cur = cur->next)
	if (Compare(cur->u.lis, stk, &ok) == ok)
	    break;
    if (cur->next) {
	POP(stk);
	exeterm(cur->u.lis->next);
    } else
	exeterm(cur->u.lis);
}
#endif
#endif
