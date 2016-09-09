/*
    module  : utils1.c
    version : 1.3
    date    : 09/09/16
*/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "globals1.h"

PUBLIC void readfactor(void)
{
    long_t set = 0;

    switch (sym) {
    case FLOAT_:
	stk = dblnode(yylval.dbl, stk);
	break;
    case '{':
	while ((sym = yylex()) != '}')
	    if (sym == CHAR_ || sym == INTEGER_)
		set |= 1 << yylval.num;
	    else
		execerror("numeric", "set");
	stk = newnode(SET_, (void *)set, stk);
	break;
    case '[':
	sym = yylex();
	readterm();
	break;
    default:
	stk = newnode(sym, yylval.ptr, stk);
	break;
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
    } while ((sym = yylex()) != ']');
}

PUBLIC void writefactor(Node *n, FILE *stm)
{
    char *p;
    int i, j;
    long_t set;

    if (!n || n == &memory[MEMORYMAX])
	execerror("non-empty stack", "print");
    switch (n->op) {
    case 0:
    case 1:
	break;
    case BOOLEAN_:
	fprintf(stm, "%s", n->u.num ? "true" : "false");
	break;
    case INTEGER_:
	fprintf(stm, "%lld", (long long)n->u.num);
	break;
    case FLOAT_:
	fprintf(stm, "%g", n->u.dbl);
	break;
    case SET_:
	fprintf(stm, "{");
	for (set = n->u.set, i = 0, j = 1; i < _SETSIZE_; i++, j <<= 1)
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
	break;
    case STRING_:
	fputc('"', stm);
	for (p = n->u.str; *p; p++) {
	    if (*p == '"' || *p == '\\' || *p == '\n')
		fputc('\\', stm);
	    fputc(*p == '\n' ? 'n' : *p, stm);
	}
	fputc('"', stm);
	break;
    case LIST_:
	fprintf(stm, "%s", "[");
	writeterm(n->u.lis, stm);
	fprintf(stm, "%s", "]");
	break;
    case USR_:
	fprintf(stm, "%s", n->u.ent->name);
	break;
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
	break;
    case ANON_FUNCT_:
	fprintf(stm, "%p", n->u.proc);
	break;
    case SYMBOL_:
	fprintf(stm, "%s", n->u.str);
	break;
    default:
	fprintf(stm, "%s", opername(n->op));
	break;
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
