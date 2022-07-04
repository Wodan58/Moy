/*
    module  : print.c
    version : 1.29
    date    : 06/19/22
*/
#include "globals.h"

void writefactor(pEnv env, Node *node)
{
    int i;
    char *ptr;
    long j, set;

    switch (node->op) {
    case USR_:
	printf("%s", dict_descr(env, node));
	break;
    case ANON_FUNCT_:
	printf("%s", procname(node->u.proc));
	break;
    case BOOLEAN_:
	printf("%s", node->u.num ? "true" : "false");
	break;
    case CHAR_:
	if (node->u.num == '\n')
	    printf("'\\n");
	else
	    printf("'%c", (int)node->u.num);
	break;
    case INTEGER_:
	printf("%ld", (long)node->u.num);
	break;
    case SET_:
	putchar('{');
	for (set = node->u.set, i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
	    if (set & j) {
		printf("%d", i);
		if ((set &= ~j) == 0)
		    break;
		putchar(' ');
	    }
	putchar('}');
	break;
    case STRING_:
	putchar('"');
	for (ptr = node->u.str; *ptr; ptr++) {
	    if (*ptr == '"' || *ptr == '\\' || *ptr == '\n')
		putchar('\\');
	    if (*ptr == '\n')
		putchar('n');
	    else
		putchar(*ptr);
	}
	putchar('"');
	break;
    case LIST_:
	putchar('[');
	writeterm(env, node->u.lis);
	putchar(']');
	break;
    case FLOAT_:
	printf("%g", node->u.dbl);
	break;
    case FILE_:
	if (!node->u.fil)
	    printf("file:NULL");
	else if (node->u.fil == stdin)
	    printf("file:stdin");
	else if (node->u.fil == stdout)
	    printf("file:stdout");
	else if (node->u.fil == stderr)
	    printf("file:stderr");
	else
	    printf("file:%p", node->u.fil);
	break;
    default:
	execerror(env, "valid datatype", "writefactor");
	break;
    }
}

void writeterm(pEnv env, Node *code)
{
    while (code) {
	writefactor(env, code);
	if (code->next)
	    putchar(' ');
	code = code->next;
    }
}

void writestack(pEnv env, Node *code)
{
    if (code) {
	if (code->next && code != code->next) {
	    writestack(env, code->next);
	    putchar(' ');
	}
	writefactor(env, code);
	if (code == code->next)
	    printf("?\n");
    }
}
