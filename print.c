/*
    module  : print.c
    version : 1.25
    date    : 08/11/19
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "joy.h"
#include "symbol.h"

void writefactor(Node *node, FILE *stm)
{
    char *ptr;
    long_t set;
    unsigned i, j;

    switch (node->op) {
    case USR_:
	fprintf(stm, "%s", dict_descr(node->u.num));
	break;
    case ANON_FUNCT_:
	if ((ptr = procname(node->u.proc)) != 0)
	    fprintf(stm, "%s", ptr);
	else
	    fprintf(stm, "%p", node->u.proc);
	break;
    case BOOLEAN_:
	fprintf(stm, "%s", node->u.num ? "true" : "false");
	break;
    case CHAR_:
	if (node->u.num == '\n')
	    fprintf(stm, "'\\n");
	else
	    fprintf(stm, "'%c", (int)node->u.num);
	break;
    case INTEGER_:
	fprintf(stm, PRINT_NUM, node->u.num);
	break;
    case SET_:
	fprintf(stm, "{");
	for (set = node->u.set, i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
	    if (set & j) {
		fprintf(stm, "%d", i);
		if ((set &= ~j) == 0)
		    break;
		fprintf(stm, " ");
	    }
	fprintf(stm, "}");
	break;
    case STRING_:
	fputc('"', stm);
	for (ptr = node->u.str; *ptr; ptr++) {
	    if (*ptr == '"' || *ptr == '\\' || *ptr == '\n')
		fputc('\\', stm);
	    fputc(*ptr == '\n' ? 'n' : *ptr, stm);
	}
	fputc('"', stm);
	break;
    case LIST_:
	fprintf(stm, "%s", "[");
	writeterm(node->u.lis, stm);
	fprintf(stm, "%s", "]");
	break;
    case FLOAT_:
	fprintf(stm, "%g", node->u.dbl);
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
    case SYMBOL_:
	fprintf(stm, "%s", node->u.str);
	break;
    case '(':
    case ')':
    case '[':
    case ']':
    case '{':
    case '}':
    case ';':
	fprintf(stm, "%c", node->op);
	break;
    case JPUBLIC:
	fprintf(stm, "JPUBLIC");
	break;
    case JPRIVATE:
	fprintf(stm, "JPRIVATE");
	break;
    case END:
	fprintf(stm, "END");
	break;
    case MODULE:
	fprintf(stm, "MODULE");
	break;
    case JEQUAL:
	fprintf(stm, "==");
	break;
    default:
	execerror("valid datatype", "writefactor");
	break;
    }
}

void writeterm(Node *code, FILE *stm)
{
    while (code) {
	writefactor(code, stm);
	if (code->next)
	    putc(' ', stm);
	code = code->next;
    }
}

void writestack(Node *code, FILE *stm)
{
    if (code) {
	if (code == code->next)
	    execerror("non-circular stack", "writestack");
	else {
	    writestack(code->next, stm);
	    putc(' ', stm);
	}
	writefactor(code, stm);
    }
}
