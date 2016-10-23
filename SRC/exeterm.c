/*
    module  : exeterm.c
    version : 1.5
    date    : 10/19/16
*/
#include "interp.h"

// #define TRACE

#ifdef TRACE
PUBLIC void printfactor(Node *node, FILE *stm)
{
    switch (node->op) {
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
	fprintf(stm, node->u.ent->name);
	return;
    case FILE_:
	fprintf(stm, "type file");
	return;
    default:
	fprintf(stm, "%s", symtab[node->op].name);
	return;
    }
}
#endif

#ifdef TRACE
static void report_symbols(void)
{
    Entry *sym;

    for (sym = symtab; sym->name; sym++)
	if (sym->is_found)
	    fprintf(stderr, "%s\n", sym->name);
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

void exeterm(Node *node)
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
    while (node) {
#ifdef STATS
	++opers;
#endif
#ifdef TRACE
	writefactor(node, stderr);
	fprintf(stderr, " . ");
	writeterm(stk, stderr);
	fprintf(stderr, "\n");
#endif
	switch (node->op) {
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
	    DUPLICATE(node);
	    break;
	case SYMBOL_:
	    break;
	case USR_:
	    if (!node->u.ent->u.body && undeferror)
		execerror("definition", node->u.ent->name);
	    if (!node->next) {
		node = node->u.ent->u.body;
		continue;
	    }
	    exeterm(node->u.ent->u.body);
	    break;
	default:
	    (*node->u.proc) ();
#ifdef TRACE
	    symtab[node->op].is_found = 1;
#endif
	    break;
	}
	node = node->next;
    }
}
