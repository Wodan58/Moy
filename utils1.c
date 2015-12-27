/*
    module  : utils1.c
    version : 1.2
    date    : 12/27/15
*/
#include <stdio.h>
#include <string.h>
#include <gc.h>
#include "globals1.h"

PUBLIC void gc_(void)
{
    GC_gcollect();
}

PUBLIC void readfactor(void)
{				/* read a JOY factor              */
    long_t set = 0;

    switch (sym) {
    case ATOM:
	lookup();
	if (location < firstlibra)
	    stk = newnode(location - symtab, (Types) location->u.proc, stk);
	else
	    stk = USR_NEWNODE(location, stk);
	return;
    case BOOLEAN_:
    case INTEGER_:
    case CHAR_:
	bucket.num = num;
    case STRING_:
	stk = newnode(sym, bucket, stk);
	return;
    case FLOAT_:
	stk = FLOAT_NEWNODE(dbl, stk);
	return;
    case '{':
	while (getsym(), sym != '}')
	    if (sym == CHAR_ || sym == INTEGER_)
		set |= 1 << num;
	    else
		execerror("numeric", "set");
	stk = SET_NEWNODE(set, stk);
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

    stk = LIST_NEWNODE(0, stk);
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

PUBLIC void writefactor(Node * n, FILE * stm)
{
    char *p;
    int i, j;
    long_t set;

    if (n == NULL)
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
	printf("{");
	for (set = n->u.set, i = 0, j = 1; i < SETSIZE; i++, j <<= 1)
	    if (set & j) {
		printf("%d", i);
		if ((set &= ~j) == 0)
		    break;
		printf(" ");
	    }
	printf("}");
	break;
    case CHAR_:
	fprintf(stm, "'%c", (int) n->u.num);
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
    case USR_:
	fprintf(stm, "%s", n->u.ent->name);
	return;
    case FILE_:
	if (n->u.fil == NULL)
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
    default:
	fprintf(stm, "%s", symtab[n->op].name);
	return;
    }
}

PUBLIC void writeterm(Node * n, FILE * stm)
{
    while (n != NULL) {
	writefactor(n, stm);
	if ((n = n->next) != NULL)
	    fprintf(stm, " ");
    }
}
