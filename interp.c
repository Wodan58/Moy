/*
    module  : interp.c
    version : 1.14
    date    : 05/12/19
*/
#include "runtime.h"
#include "runtime.c"

void interprete(Node *node)
{
    int index;
    Node *code;
#ifndef OLD_RUNTIME
    unsigned flags;
#endif

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
#ifndef OLD_RUNTIME
	case USR_:
	    index = node->u.num;
	    if ((code = dict_body(index)) != 0) {
		if ((flags = dict_flags(index)) & IS_BUILTIN) {
		    dict_setflags(index, flags | IS_USED);
		    (*(proc_t)code)();
		} else {
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
	    execerror("valid datatype", "interpreter");
	    break;
	}
    }
}

void execute(Node *node)
{
    interprete(node);
    do_stop();
}
