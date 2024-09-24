/*
 *  module  : writ.c
 *  version : 1.27
 *  date    : 09/17/24
 */
#include "globals.h"

static int spacechar = ' ';

/*
 * writefactor prints a factor in readable format to stdout.
 */
void writefactor(pEnv env, Node node, FILE *fp)
{
    int i;
    uint64_t set, j;
    char *ptr, buf[BUFFERMAX], tmp[MAXNUM];

#if 0
/*
 * This cannot happen. writefactor has a small number of customers: writeterm,
 * main, put, fput. They all check that the stack is not empty, so this code
 * only serves as a reminder for future customers.
 */
    if (!env->stck)
	execerror("non-empty stack", "print");
#endif
    switch (node.op) {
    case USR_PRIME_:
	putc('#', fp);
	goto usr_prime;

    case USR_:
usr_prime:
	fprintf(fp, "%s", vec_at(env->symtab, node.u.ent).name);
	break;

    case ANON_PRIME_:
	putc('#', fp);
	goto anon_prime;

    case ANON_FUNCT_:
anon_prime:
	fprintf(fp, "%s", opername(env, node.u.proc));
	break;

    case BOOLEAN_:
	fprintf(fp, "%s", node.u.num ? "true" : "false");
	break;

    case CHAR_:
	if (node.u.num >= 8 && node.u.num <= 13)
	    fprintf(fp, "'\\%c", "btnvfr"[node.u.num - 8]);
	else if (iscntrl(node.u.num) || node.u.num == 32)
	    fprintf(fp, "'\\%03d", (int)node.u.num);
	else
	    fprintf(fp, "'%c", (int)node.u.num);
	break;

    case INTEGER_:
	fprintf(fp, "%" PRId64, node.u.num);
	break;

    case SET_:
	putc('{', fp);
	for (i = 0, j = 1, set = node.u.set; i < SETSIZE; i++, j <<= 1)
	    if (set & j) {
		fprintf(fp, "%d", i);
		set &= ~j;
		if (set)
		    putc(spacechar, fp);
	    }
	putc('}', fp);
	break;

    case STRING_:
	putc('"', fp);
	for (ptr = node.u.str; *ptr; ptr++)
	    if (*ptr == '"')
		fprintf(fp, "\\\"");
	    else if (*ptr >= 8 && *ptr <= 13)
		fprintf(fp, "\\%c", "btnvfr"[*ptr - 8]);
	    else if (iscntrl((int)*ptr))
		fprintf(fp, "\\%03d", *ptr);
	    else
		putc(*ptr, fp);
	putc('"', fp);
	break;

    case LIST_:
	putc('[', fp);
	writeterm(env, node.u.lis, fp);
	putc(']', fp);
	break;

    case FLOAT_:
	snprintf(buf, BUFFERMAX, "%g", node.u.dbl);	/* exponent is e */
	if ((ptr = strchr(buf, '.')) == 0) {	/* locate decimal point */
	    if ((ptr = strchr(buf, 'e')) == 0) {/* locate start of exponent */
		i = buf[strlen(buf) - 1];
		if (isdigit(i))			/* check digit present */
		    strcat(buf, ".0");		/* add decimal point and 0 */
	    } else {
		strcpy(tmp, ptr);		/* save exponent */
		strcat(buf, ".0");		/* add decimal point and 0 */
		strcat(buf, tmp);		/* restore exponent */
	    }
	}
	fprintf(fp, "%s", buf);
	break;

    case FILE_:
	if (!node.u.fil)
	    fprintf(fp, "NULL");
	else if (node.u.fil == stdin)
	    fprintf(fp, "stdin");
	else if (node.u.fil == stdout)
	    fprintf(fp, "stdout");
	else if (node.u.fil == stderr)
	    fprintf(fp, "stderr");
	else
	    fprintf(fp, "%p", (void *)node.u.fil);
	break;

    case BIGNUM_:
    case USR_STRING_:
	fprintf(fp, "%s", node.u.str);
	break;
/*
 * The symbol table is not present in compiled code, but the body of
 * a quotation is. The body can be printed in a special way so as to
 * distinguish it from a normal list.
 */
    case USR_LIST_:
	if (spacechar == ' ') {
	    spacechar = ',';
	    writeterm(env, node.u.lis, fp);
	    spacechar = ' ';
	}
	break;
#if 0
/*
 * The default case does not happen: it will be flagged as a syntax error.
 */
    default:
	yyerror(env, "a factor cannot begin with this symbol");
#endif
    }
}

/*
 * spacing - write a space character, except after [ or before ].
 */
void spacing(NodeList array, Node node, FILE *fp)
{
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
 * writing - print from a stack, used by writeterm and writestack.
 */
void writing(pEnv env, NodeList array, FILE *fp)
{
    int i, j;
    Node node, temp;

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
	    for (i = 0, j = vec_size(node.u.lis); i < j; i++)
		vec_push(array, vec_at(node.u.lis, i));
	    temp.u.num = '[';
	    vec_push(array, temp);
	}
    }
}

/*
 * writeterm - print the contents of a list in readable format to stdout.
 */
void writeterm(pEnv env, NodeList list, FILE *fp)
{
    int i, j;
    NodeList array;

    if (!env->recurse)				/* print using recursion */
	for (i = vec_size(list) - 1; i >= 0; i--) {
	    writefactor(env, vec_at(list, i), fp);
	    if (i)
		putc(spacechar, fp);
	}
    else {
	vec_init(array);			/* collect nodes in a vector */
	for (i = 0, j = vec_size(list); i < j; i++)
	    vec_push(array, vec_at(list, i));
	writing(env, array, fp);
    }
}

/*
 * writestack - print the contents of the stack in readable format to stdout.
 */
void writestack(pEnv env, NodeList list, FILE *fp)
{
    int i;
    NodeList array;

    if ((i = vec_size(list)) == 0)
	return;
    vec_init(array);				/* collect nodes in a vector */
    for (--i; i >= 0; i--)
	vec_push(array, vec_at(list, i));
    writing(env, array, fp);
}
