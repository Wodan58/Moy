/*
    module  : exeterm.c
    version : 1.2
    date    : 09/09/16
*/
#include "interp.h"

#ifdef TRACE
PUBLIC void printfactor(Node *n, FILE *stm)
{
    switch (n->op) {
    case BOOLEAN_:
	fprintf(stm, "type boolean");
	return;
    case INTEGER_:
	fprintf(stm, "type integer");
	return;
    case FLOAT_:
	fprintf(stm, "type float");
	return;
    case SET_:
	fprintf(stm, "type set");
	return;
    case CHAR_:
	fprintf(stm, "type char");
	return;
    case STRING_:
	fprintf(stm, "type string");
	return;
    case LIST_:
	fprintf(stm, "type list");
	return;
    case USR_:
	fprintf(stm, n->u.ent->name);
	return;
    case FILE_:
	fprintf(stm, "type file");
	return;
    default:
	fprintf(stm, "%s", symtab[n->op].name);
	return;
    }
}
#endif

#ifdef TRACE
static void report_symbols(void)
{
    Entry *n;

    for (n = symtab; n->name; n++)
	if (n->is_used)
	    fprintf(stderr, "%s\n", n->name);
}
#endif

#ifdef STATS
static double calls, opers;

static void report_stats(void)
{
    fprintf(stderr, "%.0f calls to joy interpreter\n", calls);
    fprintf(stderr, "%.0f operations executed\n", opers);
}
#endif

void exeterm(Node *n)
{
#ifdef TRACE
    static int first;

    if (!first) {
	first = 1;
	atexit(report_symbols);
    }
#endif
#ifdef STATS
    static int stats;

    if (!stats) {
	stats = 1;
	atexit(report_stats);
    }
    ++calls;
#endif
    while (n) {
#ifdef STATS
	++opers;
#endif
#ifdef TRACE
	writefactor(n, stdout);
	printf(" . ");
	writeterm(stk, stdout);
	printf("\n");
#endif
	switch (n->op) {
	case COPIED_:
	case ILLEGAL_:
	    fprintf(stderr, "exeterm: attempting to execute bad node\n");
	    break;
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case FLOAT_:
	case SET_:
	case STRING_:
	case LIST_:
	    DUPLICATE(n);
	    break;
	case SYMBOL_:
	    break;
	case USR_:
	    if (!n->u.ent->u.body && undeferror)
		execerror("definition", n->u.ent->name);
	    if (!n->next) {
		n = n->u.ent->u.body;
		continue;
	    }
	    exeterm(n->u.ent->u.body);
	    break;
	default:
	    (*n->u.proc) ();
#ifdef TRACE
	    symtab[(int) n->op].is_used = 1;
#endif
	    break;
	}
	n = n->next;
    }
}
