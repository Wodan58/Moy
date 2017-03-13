/*
    module  : compare2.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

PRIVATE double Compare(Node *first, Node *second, int *error)
{
    char *name;

    *error = 0;
    switch (first->op) {
    case USR_:
	name = first->u.ent->name;
	switch (second->op) {
	case USR_:
	    return strcmp(name, second->u.ent->name);
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
	    return strcmp(name, printname(second->op));
	}
	break;
    case ANON_FUNCT_:
	name = procname(first->u.proc);
	switch (second->op) {
	case USR_:
	    return strcmp(name, second->u.ent->name);
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
	    return strcmp(name, printname(second->op));
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
	    return first->u.num - second->u.num;
	case SET_:
	case SYMBOL_:
	case STRING_:
	case LIST_:
	    break;
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
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	    break;
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
	case USR_:
	    return strcmp(name, second->u.ent->name);
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
	    return strcmp(name, printname(second->op));
	}
	break;
    case LIST_:
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
	name = printname(first->op);
	switch (second->op) {
	case USR_:
	    return strcmp(name, second->u.ent->name);
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
	    return strcmp(name, printname(second->op));
	}
	break;
    }
    *error = 1;
    return 0;
}
