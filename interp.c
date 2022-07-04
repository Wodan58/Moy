/*
    module  : interp.c
    version : 1.20
    date    : 06/19/22
*/
#include "runtime.h"
#include "builtin.c"

#define TRACING

#ifdef REPORT
double count_execute;

static void report_execute(void)
{
    fprintf(stderr, "execute = %.0f\n", count_execute);
}
#endif

void exeterm(pEnv env, Node *node)
{
    Node *cur;
#ifdef COMPILING
    int index;
    char *name;
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

#ifdef COMPILING
start:
#endif
    for (cur = node; cur; cur = cur->next) {
#ifdef TRACING
	if (debugging) {
	    writestack(env, env->stk);
	    printf(" : ");
	    writeterm(env, cur);
	    putchar('\n');
	}
#endif
	switch (cur->op) {
	case ANON_FUNCT_:
	    (*cur->u.proc)(env);
	    break;
	case USR_:
#ifdef COMPILING
	    index = cur->u.num;
	    code = dict_body(env, index);
	    if (code) {
		flags = dict_flags(env, index);
		if (flags & IS_BUILTIN)
		    (*(proc_t)code)(env);
		else {
		    if (!compiling) {
			if (!cur->next) {
			    node = code;
			    goto start;
			}
			exeterm(env, code);
		    } else {
			if ((flags & (IS_ACTIVE | IS_USED)) == 0) {
			    dict_setflags(env, index, flags | IS_ACTIVE);
			    exeterm(env, code);
		    	    flags = dict_flags(env, index);
		    	    dict_setflags(env, index, flags & ~IS_ACTIVE);
			    break;
			}
			name = dict_nickname(env, index);
			if ((flags & IS_DECLARED) == 0) {
			    flags |= IS_DECLARED;
			    fprintf(declfp, "void do_%s(pEnv env);", name);
			}
			printstack(env);
			fprintf(outfp, "do_%s(env);", name);
		    }
		}
		dict_setflags(env, index, flags | IS_USED);
	    } else if (undeferror)
		execerror(env, "definition", dict_descr(env, cur));
#endif
	    break;
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	case STRING_:
	case LIST_:
	case FLOAT_:
	case FILE_:
	    DUPLICATE(cur);
	    break;
	default:
	    execerror(env, "valid datatype", "exeterm");
	    break;
	}
    }
}

void execute(pEnv env, Node *node)
{
    exeterm(env, node);
    do_stop(env);
}

/*
    execerror - print a runtime error to stderr. When compiling print the
		function instead of generating an error.
*/
void execerror(pEnv env, char *message, const char *op)
{
    if (!compiling) {
	fflush(stdout);
	fprintf(stderr, "run time error: %s needed for %s\n", message, op);
	abortexecution();
    }
#ifdef COMPILING
    if (strncmp(message, "definition", 10)) {
	printstack(env);
	fprintf(outfp, "do_%s(env);", dict_translate(env, op));
    }
#endif
}
