/*
    module  : interp.c
    version : 1.17
    date    : 03/15/21
*/
#include "runtime.h"
#include "builtin.c"

#define DEBUG

#ifdef REPORT
double count_execute;

static void report_execute(void)
{
    fprintf(stderr, "execute = %.0f\n", count_execute);
}
#endif

void interprete(pEnv env, Node *node)
{
    Node *cur;
#ifndef OLD_RUNTIME
    int index;
    Node *code;
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

#ifndef OLD_RUNTIME
start:
#endif
    for (cur = node; cur; cur = cur->next) {
#ifdef DEBUG
	if (debugging) {
	    writestack(env, env->stk, stderr);
	    fprintf(stderr, " : ");
	    writeterm(env, cur, stderr);
	    fprintf(stderr, "\n");
	}
#endif
	switch (cur->op) {
#ifndef OLD_RUNTIME
	case USR_:
	    index = cur->u.num;
	    if ((code = dict_body(env, index)) != 0) {
		if ((flags = dict_flags(env, index)) & IS_BUILTIN) {
		    dict_setflags(env, index, flags | IS_USED);
		    (*(proc_t)code)(env);
		} else {
		    if (!cur->next) {
			node = code;
			goto start;
		    }
		    interprete(env, code);
		}
	    } else if (undeferror)
		execerror("definition", dict_descr(env, index));
	    break;
#endif
	case ANON_FUNCT_:
	    (*cur->u.proc)(env);
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
	    DUPLICATE(cur);
	    break;
	default:
	    execerror("valid datatype", "interpreter");
	    break;
	}
    }
}

void execute(pEnv env, Node *node)
{
    interprete(env, node);
    do_stop(env);
}
