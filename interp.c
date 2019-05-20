/*
    module  : interp.c
    version : 1.15
    date    : 05/20/19
*/
#include "runtime.h"
#include "runtime.c"

#ifdef REPORT
double count_execute;

void report_execute()
{
    fprintf(stderr, "execute = %.0f\n", count_execute);
}
#endif

void interprete(Node *node)
{
    int index;
    Node *code;
#ifndef OLD_RUNTIME
    unsigned flags;
#endif
#ifdef REPORT
    static int first;

    if (!first) {
	first = 1;
	atexit(report_execute);
    }
    count_execute++;
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
