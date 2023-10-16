/*
 *  module  : writ.c
 *  version : 1.14
 *  date    : 10/12/23
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
    if (!env->stck)
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
	fprintf(fp, "%s", opername(node.u.proc));
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
    case INTEGER_:
    case KEYWORD_:
	fprintf(fp, "%" PRId64, node.u.num);
	if (node.op == KEYWORD_)
	    fputc('\'', fp);
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
	    fprintf(fp, "file:%p", (void *)node.u.fil);
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
PRIVATE void spacing(void *parm, Node node, FILE *fp)
{
    vector(Node) *array = parm;

    if (node.op == CHAR_ && node.u.num == '[')	/* inspect preceding node */
	;
    else if (vec_size(array)) {			/* inspect following node */
	node = vec_back(array);
	if (node.op == CHAR_ && (node.u.num == '[' || node.u.num == ']'))
	    ;
	else
	    putc(spacechar, fp);
    }
}

/*
    writing - print from a stack, used by writeterm and writestack.
*/
PRIVATE void writing(pEnv env, void *parm, FILE *fp)
{
    int i, j;
    Node node, temp;
    vector(Node) *array = parm;

    while (vec_size(array)) {
	node = vec_pop(array);
	if (node.op != LIST_) {
	    if (node.op == CHAR_ && (node.u.num == '[' || node.u.num == ']'))
		putc((int)node.u.num, fp);
	    else 
		writefactor(env, node, fp);
	    spacing(array, node, fp);
	} else {
	    temp.u.num = ']';
	    temp.op = CHAR_;
	    vec_push(array, temp);
	    for (i = 0, j = pvec_cnt(node.u.lis); i < j; i++)
		vec_push(array, pvec_nth(node.u.lis, i));
	    temp.u.num = '[';
	    vec_push(array, temp);
	}
    }
}

/*
    writeterm - print the contents of a list in readable format to stdout.
*/
PUBLIC void writeterm(pEnv env, NodeList *list, FILE *fp)
{
    int i, j;
    vector(Node) *array;

    if ((j = pvec_cnt(list)) == 0)
	return;
    vec_init(array);				/* collect nodes in a vector */
    for (i = 0; i < j; i++)
	vec_push(array, pvec_nth(list, i));
    writing(env, (void *)array, fp);
}

/*
    writestack - print the contents of the stack in readable format to stdout.
*/
#ifdef TRACING
PUBLIC void writestack(pEnv env, NodeList *list, FILE *fp)
{
    int i, j;
    vector(Node) *array;

    if ((j = pvec_cnt(list)) == 0)
	return;
    vec_init(array);				/* collect nodes in a vector */
    for (i = j - 1; i >= 0; i--)
	vec_push(array, pvec_nth(list, i));
    writing(env, (void *)array, fp);
}
#endif
