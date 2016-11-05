/*
    module  : arity.c
    version : 1.6
    date    : 11/05/16
*/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "globals1.h"
#include "utstring.h"

#define P(x)		utstring_printf(str, x)
#define Q(x, y)		utstring_printf(str, x, y)

char *aritysym(int op);
void arityterm(Node *cur, UT_string *str);

void arityfactor(Node *cur, UT_string *str)
{
    Entry *sym;

    switch (cur->op) {
    case BOOLEAN_:
    case INTEGER_:
    case FLOAT_:
    case SET_:
    case CHAR_:
    case STRING_:
    case LIST_:
    case FILE_:
	P("A");
	break;
    case USR_:
	sym = cur->u.ent;
	if (!sym->is_marked) {
	    sym->is_marked = 1;
	    arityterm(sym->u.body, str);
	    sym->is_marked = 0;
	}
	break;
    case ANON_FUNCT_:
    case SYMBOL_:
	P("?");
	break;
    default:
	Q("%s", aritysym(cur->op));
	break;
    }
}

int tally(char *str)
{
    int d;
    char *ptr;

    if (strchr(str, '?'))
	return MEMORYMAX;
    for (d = 0; *str; str++)
	if (*str == 'D')
	    d++;
	else if (*str == 'A')
	    if ((ptr = strchr(str, 'D')) != 0)
		*ptr = *str = ' ';
    return d;
}

void arityterm(Node *cur, UT_string *str)
{
    int sp, a[4], q[5];

    for (sp = 0; cur; cur = cur->next) {
	if (cur->op == LIST_) {
	    q[sp++] = arity(cur->u.lis);
	    if (sp == 5) {
		q[0] = q[1];
		q[1] = q[2];
		q[2] = q[3];
		q[3] = q[4];
		sp = 4;
	    }
	    P("A");
	    continue;
	}
	switch (cur->op + FALSE - FALSE_) {
	case ALL:
	case BINARY:
	case DIP:
	case FILTER:
	case FOLD:
	case I:
	case INFRA:
	case MAP:
	case NULLARY:
	case SOME:
	case SPLIT:
	case STEP:
	case TERNARY:
	case TIMES:
	case TREESTEP:
	case UNARY:
	case UNARY2:
	case UNARY3:
	case UNARY4:
	case X:
	    if (!sp || (a[0] = q[sp - 1]) == MEMORYMAX)
		P("?");
	    else
		while (a[0]--)
		    P("D");
	    break;
	case BRANCH:
	case CLEAVE:
	case IFCHAR:
	case IFFILE:
	case IFFLOAT:
	case IFINTEGER:
	case IFLIST:
	case IFLOGICAL:
	case IFSET:
	case IFSTRING:
	case PRIMREC:
	case TREEREC:
	case WHILE:
	    if (sp < 2 || (a[0] = q[sp - 1]) == MEMORYMAX ||
			  (a[1] = q[sp - 2]) == MEMORYMAX)
		P("?");
	    else {
		if (a[0] < a[1])
		    a[0] = a[1];
		while (a[0]--)
		    P("D");
	    }
	    break;
	case IFTE:
	case TAILREC:
	case TREEGENREC:
	    if (sp < 3 || (a[0] = q[sp - 1]) == MEMORYMAX ||
			  (a[1] = q[sp - 2]) == MEMORYMAX ||
			  (a[2] = q[sp - 3]) == MEMORYMAX)
		P("?");
	    else {
		if (a[0] < a[1])
		    a[0] = a[1];
		if (a[0] < a[2])
		    a[0] = a[2];
		while (a[0]--)
		    P("D");
	    }
	    break;
	case BINREC:
	case GENREC:
	case LINREC:
	    if (sp < 4 || (a[0] = q[sp - 1]) == MEMORYMAX ||
			  (a[1] = q[sp - 2]) == MEMORYMAX ||
			  (a[2] = q[sp - 3]) == MEMORYMAX ||
			  (a[3] = q[sp - 4]) == MEMORYMAX)
		P("?");
	    else {
		if (a[0] < a[1])
		    a[0] = a[1];
		if (a[0] < a[2])
		    a[0] = a[2];
		if (a[0] < a[3])
		    a[0] = a[3];
		while (a[0]--)
		    P("D");
	    }
	    break;
	case CASE:
	case COND:
	case CONDLINREC:
	case CONDNESTREC:
	case CONSTRUCT:
	    P("?");
	    break;
	default:
	    arityfactor(cur, str);
	    break;
	}
	sp = 0;
    }
}

int arity(Node *cur)
{
    int num;
    char *ptr;
    UT_string *str;

    utstring_new(str);
    arityterm(cur, str);
    ptr = utstring_body(str);
    num = tally(ptr);
    return num;
}
