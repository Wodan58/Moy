/*
    module  : utils1.c
    version : 1.12
    date    : 10/19/16
*/
#include <stdio.h>
#include <time.h>
#include "globals1.h"
#include "memory.h"
#include "compile.h"

PUBLIC void readfactor(void)
{
    long_t set = 0;

    switch (sym) {
    case FLOAT_:
	stk = FLOAT_NEWNODE(yylval.dbl, stk);
	break;
    case '{':
	while ((sym = yylex()) != '}')
	    if (sym == CHAR_ || sym == INTEGER_)
		set |= 1 << yylval.num;
	    else
		execerror("numeric", "set");
	stk = SET_NEWNODE(set, stk);
	break;
    case '[':
	sym = yylex();
	readterm();
	break;
    default:
	GNULLARY(sym, yylval.ptr);
	break;
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
    } while ((sym = yylex()) != ']');
}

PUBLIC void writefactor(Node *node, FILE *stm)
{
    static int in_quot;
    char *p;
    int i, j;
    long_t set;

    if (!node || node == &memory[MEMORYMAX])
	execerror("non-empty stack", "print");
    switch (node->op) {
    case 0:
	fprintf(stm, "%s", node->u.str);
	break;
    case BOOLEAN_:
	fprintf(stm, "%s", node->u.num ? "true" : "false");
	break;
    case INTEGER_:
	fprintf(stm, "%lld", (long long)node->u.num);
	break;
    case FLOAT_:
	fprintf(stm, "%g", node->u.dbl);
	break;
    case SET_:
	fprintf(stm, "{");
	for (set = node->u.set, i = 0, j = 1; i < _SETSIZE_; i++, j <<= 1)
	    if (set & j) {
		fprintf(stm, "%d", i);
		if ((set &= ~j) == 0)
		    break;
		fprintf(stm, " ");
	    }
	fprintf(stm, "}");
	break;
    case CHAR_:
	fprintf(stm, "'%c", (int)node->u.num);
	break;
    case STRING_:
	fputc('"', stm);
	for (p = node->u.str; *p; p++) {
	    if (*p == '"' || *p == '\\' || *p == '\n')
		fputc('\\', stm);
	    fputc(*p == '\n' ? 'n' : *p, stm);
	}
	fputc('"', stm);
	break;
    case LIST_:
	in_quot++;
	fprintf(stm, "%s", "[");
	writeterm(node->u.lis, stm);
	fprintf(stm, "%s", "]");
	in_quot--;
	break;
    case USR_:
	if (node->unmark)
	    fprintf(stm, "`");
	fprintf(stm, "%s", node->u.ent->name);
	break;
    case FILE_:
	if (!node->u.fil)
	    fprintf(stm, "file:NULL");
	else if (node->u.fil == stdin)
	    fprintf(stm, "file:stdin");
	else if (node->u.fil == stdout)
	    fprintf(stm, "file:stdout");
	else if (node->u.fil == stderr)
	    fprintf(stm, "file:stderr");
	else
	    fprintf(stm, "file:%p", node->u.fil);
	break;
    case ANON_FUNCT_:
	fprintf(stm, "%p", node->u.proc);
	break;
    case SYMBOL_:
	if (node->unmark)
	    fprintf(stm, "`");
	fprintf(stm, "%s", node->u.str);
	break;
    default:
	if (node->unmark)
	    fprintf(stm, "`");
	fprintf(stm, "%s", opername(node->op));
	break;
    }
}

PUBLIC void writeterm(Node *node, FILE *stm)
{
    while (node && node != &memory[MEMORYMAX]) {
	writefactor(node, stm);
	if ((node = node->next) != 0)
	    fprintf(stm, " ");
    }
}

PUBLIC Node *copyterm(Node *node)
{
    Entry *sym;
    Node *root = 0, **cur;

    for (cur = &root; node; node = node->next) {
	*cur = malloc(sizeof(Node));
	**cur = *node;
	(*cur)->next = 0;
	if (node->op == USR_) {
	    sym = node->u.ent;
	    if (sym->u.body) {
		if (!sym->is_used) {
		    sym->is_used = 1;
		    **cur = *copyterm(sym->u.body);
		} else if (!sym->uniq)
		    sym->uniq = ++identifier;
	    }
	}
	do
	    cur = &(*cur)->next;
	while (*cur);
    }
    return root;
}
