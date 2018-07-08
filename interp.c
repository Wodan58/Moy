/*
    module  : interp.c
    version : 1.11
    date    : 07/08/18
*/
#include "runtime.h"
#include "runtime.c"

void interprete(Node *node)
{
    int index;
    Node *code;

start:
    for (; node; node = node->next) {
#ifdef DEBUG
	if (debugging) {
	    writestack(stk, stderr);
	    fprintf(stderr, " : ");
	    writeterm(node, stderr);
	    fprintf(stderr, "\n");
	}
#endif
	switch (node->op) {
#ifndef NCHECK
	case USR_:
	    index = node->u.num;
	    if ((code = dict_body(index)) != 0) {
		if (dict_flags(index) & IS_BUILTIN)
		    (*(proc_t)code)();
		else {
		    if (!node->next) {
			node = code;
			goto start;
		    }
		    interprete(code);
		}
	    } else if (undeferror)
		execerror("definition", dict_descr(index));
	    break;
#endif
	case ANON_FUNCT_:
	    (*node->u.proc)();
	    break;
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	case STRING_:
	case LIST_:
	case FLOAT_:
	case FILE_:
	case SYMBOL_:
	    DUPLICATE(node);
	    break;
	default:
	    execerror("valid datatype", "interprete");
	    break;
	}
    }
}

void execute(Node *node)
{
    interprete(node);
    do_stop();
}
