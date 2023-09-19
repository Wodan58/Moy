/*
 *  module  : writ.c
 *  version : 1.12
 *  date    : 09/19/23
 */
#include "globals.h"

static int spacechar = ' ';

/*
    writefactor - print a factor in readable format to stdout.
*/
PUBLIC void writefactor(pEnv env, Node node, FILE *fp)
{
    int i;
    char *ptr;

/*
    This cannot happen. writefactor has a small number of customers: writeterm,
    main, put, fput. They all check that the stack is not empty, so this code
    only serves as a reminder for future customers.
*/
#if 0
    if (!n)
	execerror(env->filename, "non-empty stack", "print");
#endif
    switch (node.op) {
    case USR_:
    case USR_PRIME_:
	fprintf(fp, "%s", vec_at(env->symtab, node.u.ent).name);
	if (node.op == USR_PRIME_)
	    putc('\'', fp);
	break;
    case ANON_FUNCT_:
    case ANON_PRIME_:
	fprintf(fp, "%s", cmpname(node.u.proc));
	if (node.op == ANON_PRIME_)
	    putc('\'', fp);
	break;
    case BOOLEAN_:
	fprintf(fp, "%s", node.u.num ? "true" : "false");
	break;
    case CHAR_:
	if (node.u.num >= 8 && node.u.num <= 13)
	    fprintf(fp, "'\\%c", "btnvfr"[node.u.num - 8]);
	else
	    fprintf(fp, "'%c", (int)node.u.num);
	break;
    case UNKNOWN_:
    case INTEGER_:
	fprintf(fp, "%" PRId64, node.u.num);
	if (node.op == UNKNOWN_)
	    fputc('\\', fp);
	break;
    case SET_:
	putc('{', fp);
	for (i = 0; i < SETSIZE; i++)
	    if (node.u.set & ((int64_t)1 << i)) {
		fprintf(fp, "%d", i);
		node.u.set &= ~((int64_t)1 << i);
		if (node.u.set)
		    putc(spacechar, fp);
	    }
	putc('}', fp);
	break;
    case STRING_:
	putc('"', fp);
	for (ptr = node.u.str; ptr && *ptr; ptr++) {
	    if (*ptr >= 8 && *ptr <= 13)
		fprintf(fp, "\\%c", "btnvfr"[*ptr - 8]);
	    else
		putc(*ptr, fp);
	}
	putc('"', fp);
	break;
#if 0
    case LIST_:
	putc('[', fp);
	writeterm(env, node.u.lis, fp);
	putc(']', fp);
	break;
#endif
    case FLOAT_:
	fprintf(fp, "%g", node.u.dbl);
	break;
    case FILE_:
	if (!node.u.fil)
	    fprintf(fp, "file:NULL");
	else if (node.u.fil == stdin)
	    fprintf(fp, "file:stdin");
	else if (node.u.fil == stdout)
	    fprintf(fp, "file:stdout");
	else if (node.u.fil == stderr)
	    fprintf(fp, "file:stderr");
	else
	    fprintf(fp, "file:%p", node.u.fil);
	break;
    case BIGNUM_:
    case USR_STRING_:
	fprintf(fp, "%s", node.u.str);
	break;
/*
    The symbol table is not present in compiled code, but the body of
    a quotation is. The body can be printed in a special way so as to
    distinguish it from a normal list.
*/
    case USR_LIST_:
	if (spacechar == ' ') {
	    spacechar = ',';
	    writeterm(env, node.u.lis, fp);
	    spacechar = ' ';
	}
	break;
#if 0
    default:
	yyerror(env, "a factor cannot begin with this symbol");
#endif
    }
}

/*
    spacing - write a space character, except after [ or before ].
*/
PRIVATE void spacing(NodeList *stack, Node node, FILE *fp)
{
    if (node.op == CHAR_ && node.u.num == '[') /* inspect preceding node */
	;
    else if (lst_size(stack)) { /* inspect following node */
	node = lst_back(stack);
	if (node.op == CHAR_ && (node.u.num == '[' || node.u.num == ']'))
	    ;
	else
	    putc(spacechar, fp);
    }
}

/*
    writing - print from a stack, used by writeterm and writestack.
*/
PRIVATE void writing(pEnv env, NodeList *stack, FILE *fp)
{
    int i, j;
    Node node, temp;

    while (lst_size(stack)) {
	node = lst_pop(stack);
	if (node.op != LIST_) {
	    if (node.op == CHAR_ && (node.u.num == '[' || node.u.num == ']'))
		putc((int)node.u.num, fp);
	    else 
		writefactor(env, node, fp);
	    spacing(stack, node, fp);
	} else {
	    temp.u.num = ']';
	    temp.op = CHAR_;
	    lst_push(stack, temp);
	    for (i = 0, j = lst_size(node.u.lis); i < j; i++) {
		temp = lst_at(node.u.lis, i);
		lst_push(stack, temp);
	    }
	    temp.u.num = '[';
	    temp.op = CHAR_;
	    lst_push(stack, temp);
	}
    }
}

/*
    writeterm - print the contents of a list in readable format to stdout.
*/
PUBLIC void writeterm(pEnv env, NodeList *list, FILE *fp)
{
    Node node;
    NodeList *stack = 0;
    int i, j = lst_size(list);

    if (j)
	lst_init(stack);
    for (i = 0; i < j; i++) {
	node = lst_at(list, i);
	lst_push(stack, node);
    }
    writing(env, stack, fp);
}

/*
    writestack - print the contents of the stack in readable format to stdout.
*/
#ifdef TRACING
PUBLIC void writestack(pEnv env, NodeList *list, FILE *fp)
{
    Node node;
    NodeList *stack = 0;
    int i, j = lst_size(list);

    if (j)
	lst_init(stack);
    for (i = j - 1; i >= 0; i--) {
	node = lst_at(list, i);
	lst_push(stack, node);
    }
    writing(env, stack, fp);
}
#endif
