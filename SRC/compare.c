/*
    module  : compare.c
    version : 1.2
    date    : 09/09/16
*/
#include "interp.h"

/* compare.c */
PRIVATE double Compare(Node *first, Node *second, int *error)
{
    *error = 0;
    switch (first->op) {
    case USR_:
	switch (second->op) {
	case USR_:
	    return strcmp(first->u.ent->name, second->u.ent->name);
	case ANON_FUNCT_:
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	    break;
	case SYMBOL_:
	case STRING_:
	    return strcmp(first->u.ent->name, second->u.str);
	case LIST_:
	case FLOAT_:
	case FILE_:
	    break;
	default:
	    return strcmp(first->u.ent->name, opername(second->op));
	}
	break;
    case ANON_FUNCT_:
	switch (second->op) {
	case USR_:
	    break;
	case ANON_FUNCT_:
	    return (size_t) first->u.proc - (size_t) second->u.proc;
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	case SYMBOL_:
	case STRING_:
	case LIST_:
	case FLOAT_:
	case FILE_:
	default:
	    break;
	}
	break;
    case BOOLEAN_:
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
    case CHAR_:
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
	switch (second->op) {
	case USR_:
	    return strcmp(first->u.str, second->u.ent->name);
	case ANON_FUNCT_:
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	    break;
	case SYMBOL_:
	case STRING_:
	    return strcmp(first->u.str, second->u.str);
	case LIST_:
	case FLOAT_:
	case FILE_:
	    break;
	default:
	    return strcmp(first->u.str, opername(second->op));
	}
	break;
    case LIST_:
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
	case FILE_:
	default:
	    break;
	}
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
	switch (second->op) {
	case USR_:
	    return strcmp(opername(first->op), second->u.ent->name);
	case ANON_FUNCT_:
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	    break;
	case SYMBOL_:
	case STRING_:
	    return strcmp(opername(first->op), second->u.str);
	case LIST_:
	case FLOAT_:
	case FILE_:
	    break;
	default:
	    return strcmp(opername(first->op), opername(second->op));
	}
	break;
    }
    *error = 1;
    return 0;
}
