/*
    module  : interp.c
    version : 1.9
    date    : 06/29/18
*/
#include "runtime.h"
#include "runtime.c"

#ifndef RUNTIME
static int direct;
#endif

void interprete(Node *code)
{
    int index;
    Node *node;
    unsigned flags;
#ifndef RUNTIME
    char *name;
#endif

start:
    for (; code; code = code->next) {
#ifdef DEBUG
	if (debugging) {
	    writestack(stk, stderr);
	    fprintf(stderr, " . ");
	    writeterm(code, stderr);
	    fprintf(stderr, "\n");
	}
#endif
	switch (code->op) {
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	case STRING_:
	case LIST_:
	case FLOAT_:
	case FILE_:
	case SYMBOL_:
#ifndef RUNTIME
	    if (optimizing) {
		if (code->op == LIST_ && code->u.lis)
		    add_history2(LIST_, code->u.lis->op);
		else
		    add_history(code->op);
	    }
#endif
	    DUPLICATE(code);
	    break;
#ifndef RUNTIME
	case USR_:
	    index = code->u.num;
	    flags = dict_flags(index);
	    if ((node = dict_body(index)) == 0 && undeferror)
		execerror("definition", dict_name(index));
	    else if (node && flags & IS_BUILTIN)
		(*(proc_t)node)();
	    else if (node) {
		if (compiling) {
		    if (direct)
			printstack(outfp);
		    flags |= IS_USED;
		    if ((flags & IS_ACTIVE) == 0) {
			dict_setflags(index, flags | IS_ACTIVE);
			interprete(node);
		    } else {
			name = dict_nickname(index);
			if ((flags & IS_DECLARED) == 0) {
			    flags |= IS_DECLARED;
			    fprintf(declfp, "void do_%s(void);", name);
			}
			fprintf(outfp, "do_%s();", name);
		    }
		    dict_setflags(index, flags);
		    break;
		}
		if (!code->next) {
		    code = node;
		    goto start;
		}
		interprete(node);
	    }
	    continue;
#endif
	case ANON_FUNCT_:
	    (*code->u.proc)();
	    break;
	default:
	    execerror("valid datatype", "interprete");
	    break;
	}
    }
}

void execute(Node *code)
{
    interprete(code);
    do_stop();
}

#ifndef RUNTIME
void evaluate(Node *code)
{
    NewScope();
    interprete(code);
    printstack(outfp);
    OldScope();
}

void evaluate1(Node *code)
{
    direct = 1;
    evaluate(code);
    direct = 0;
}

void evaluate2(Node *code, int num)
{
    if (num == START_SCOPE || num == INIT_SCOPE)
	NewScope();
    if (num == INIT_SCOPE)
	return;
    if (num != STOP_SCOPE) {
	interprete(code);
	printstack(outfp);
    }
    if (num == END_SCOPE || num == STOP_SCOPE)
	OldScope();
}
#endif
