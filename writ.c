/*
 *  module  : writ.c
 *  version : 1.22
 *  date    : 04/11/24
 */
#include "globals.h"

static int spacechar = ' ';

/*
 * writefactor - print a factor in readable format to stdout.
 */
void writefactor(pEnv env, Node node, FILE *fp)
{
    int i;
    uint64_t set, j;
    char *ptr, buf[MAXNUM], tmp[MAXNUM];

#if 0
/*
 * This cannot happen. writefactor has a small number of customers: writeterm,
 * main, put, fput. They all check that the stack is not empty, so this code
 * only serves as a reminder for future customers.
 */
    if (!env->stck)
	execerror(env->filename, "non-empty stack", "print");
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
	else if (iscntrl((int)node.u.num) || node.u.num == 32)
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
	for (ptr = node.u.str; ptr && *ptr; ptr++)
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
	sprintf(buf, "%g", node.u.dbl);		/* exponent character is e */
	if ((ptr = strchr(buf, '.')) == 0) {	/* locate decimal point */
	    if ((ptr = strchr(buf, 'e')) == 0)  /* locate start of exponent */
		strcat(buf, ".0");		/* append decimal point + 0 */
	    else {
		strcpy(tmp, ptr);		/* save exponent */
		sprintf(ptr, ".0%s", tmp);	/* insert decimal point + 0 */
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

    default:
	yyerror(env, "a factor cannot begin with this symbol");
    }
}

/*
 * spacing - write a space character, except after [ or before ].
 */
void spacing(void *parm, Node node, FILE *fp)
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
 * writing - print from a stack, used by writeterm and writestack.
 */
void writing(pEnv env, void *parm, FILE *fp)
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
 * writeterm - print the contents of a list in readable format to stdout.
 */
void writeterm(pEnv env, NodeList *list, FILE *fp)
{
    int i, j;
    vector(Node) *array;

    if ((j = pvec_cnt(list)) == 0)
	return;
    if (!env->recurse)				/* print using recursion */
	for (i = j - 1; i >= 0; i--) {
	    writefactor(env, pvec_nth(list, i), fp);
	    if (i)
		putchar(' ');
	}
    else {
	vec_init(array);			/* collect nodes in a vector */
	for (i = 0; i < j; i++)
	    vec_push(array, pvec_nth(list, i));
	writing(env, (void *)array, fp);
    }
}

/*
 * writestack - print the contents of the stack in readable format to stdout.
 */
void writestack(pEnv env, NodeList *list, FILE *fp)
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
