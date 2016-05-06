/*
    module  : utils1.c
    version : 1.2
    date    : 05/06/16
*/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "globals1.h"

PUBLIC void readfactor(void)
{
    long_t set = 0;

    switch (sym) {
    case ATOM:
	lookup();
	if (location < firstlibra)
	    stk = newnode(location - symtab, location->u.proc, stk);
	else
	    stk = newnode(USR_, location, stk);
	return;
    case BOOLEAN_:
    case INTEGER_:
    case CHAR_:
	bucket.num = num;
    case STRING_:
	stk = newnode(sym, bucket.ptr, stk);
	return;
    case FLOAT_:
	stk = dblnode(dbl, stk);
	return;
    case '{':
	while (getsym(), sym != '}')
	    if (sym == CHAR_ || sym == INTEGER_)
		set |= 1 << num;
	    else
		execerror("numeric", "set");
	stk = newnode(SET_, (void *)set, stk);
	return;
    case '[':
	getsym();
	readterm();
	return;
    }
}

PUBLIC void readterm(void)
{
    Node **cur;

    stk = newnode(LIST_, 0, stk);
    if (sym == ']')
	return;
    cur = &stk->u.lis;
    do {
	readfactor();
	*cur = stk;
	 cur = &stk->next;
	 stk = *cur;
	*cur = 0;
    } while (getsym(), sym != ']');
}

PUBLIC void writefactor(Node *n, FILE *stm)
{
    char *p;
    int i, j;
    long_t set;

    if (!n || n == &memory[MEMORYMAX])
	execerror("non-empty stack", "print");
    switch (n->op) {
    case BOOLEAN_:
	fprintf(stm, "%s", n->u.num ? "true" : "false");
	return;
    case INTEGER_:
	fprintf(stm, "%lld", (long long)n->u.num);
	return;
    case FLOAT_:
	fprintf(stm, "%g", n->u.dbl);
	return;
    case SET_:
	fprintf(stm, "{");
	for (set = n->u.set, i = 0, j = 1; i < SETSIZE; i++, j <<= 1)
	    if (set & j) {
		fprintf(stm, "%d", i);
		if ((set &= ~j) == 0)
		    break;
		fprintf(stm, " ");
	    }
	fprintf(stm, "}");
	break;
    case CHAR_:
	fprintf(stm, "'%c", (int)n->u.num);
	return;
    case STRING_:
	fputc('"', stm);
	for (p = n->u.str; *p; p++) {
	    if (*p == '"' || *p == '\\' || *p == '\n')
		fputc('\\', stm);
	    fputc(*p == '\n' ? 'n' : *p, stm);
	}
	fputc('"', stm);
	return;
    case LIST_:
	fprintf(stm, "%s", "[");
	writeterm(n->u.lis, stm);
	fprintf(stm, "%s", "]");
	return;
    case SYMBOL_:
	fprintf(stm, "%s", n->u.str);
	return;
    case USR_:
	fprintf(stm, "%s", n->u.ent->name);
	return;
    case FILE_:
	if (!n->u.fil)
	    fprintf(stm, "file:NULL");
	else if (n->u.fil == stdin)
	    fprintf(stm, "file:stdin");
	else if (n->u.fil == stdout)
	    fprintf(stm, "file:stdout");
	else if (n->u.fil == stderr)
	    fprintf(stm, "file:stderr");
	else
	    fprintf(stm, "file:%p", n->u.fil);
	return;
    case JSymbol:
	fprintf(stm, "%s", n->u.str);
	break;
    default:
	fprintf(stm, "%s", symtab[n->op].name);
	return;
    }
}

PUBLIC void writeterm(Node *n, FILE *stm)
{
    while (n && n != &memory[MEMORYMAX]) {
	writefactor(n, stm);
	if ((n = n->next) != 0)
	    fprintf(stm, " ");
    }
}
