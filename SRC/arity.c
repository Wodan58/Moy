/*
    module  : arity.c
    version : 1.5
    date    : 10/16/16
*/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "globals1.h"
#include "utstring.h"

#define rebase(x)	(x - FALSE + FALSE_)

#define P(x)		utstring_printf(str, x)
#define Q(x, y)		utstring_printf(str, x, y)

void genrecaux(void);
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
	if (cur->u.ptr == genrecaux) {
	    P("DA");
	    break;
	}
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
    int d = 0;
    char *ptr;

    if (strchr(str, '?'))
	return MEMORYMAX;
    for ( ; *str; str++) {
	if (*str == 'A')
	    if ((ptr = strchr(str, 'D')) != 0)
		*ptr = *str = ' ';
	if (*str == 'D')
	    d++;
    }
    return d;
}

void arityterm(Node *cur, UT_string *str)
{
    int d[2];
    UT_string *tmp[2];

    for ( ; cur; cur = cur->next) {
	if (cur->op == LIST_ && cur->next &&
		   (cur->next->op == rebase(I) ||
		    cur->next->op == rebase(X) ||
		    cur->next->op == rebase(DIP) ||
		    cur->next->op == rebase(SOME) ||
		    cur->next->op == rebase(ALL) ||
		    cur->next->op == rebase(STEP))) {
	    arityterm(cur->u.lis, str);
	    cur = cur->next;
	} else if (cur->op == LIST_ && cur->next &&
		   cur->next->op == LIST_ && cur->next->next &&
		   cur->next->next->op == LIST_ && cur->next->next->next &&
		   cur->next->next->next->op == rebase(IFTE)) {
	    utstring_new(tmp[0]);
	    arityterm(cur->next->u.lis, tmp[0]);	/* TRUE branch */
	    d[0] = tally(utstring_body(tmp[0]));
	    utstring_new(tmp[1]);
	    arityterm(cur->next->next->u.lis, tmp[1]);	/* FALSE branch */
	    d[1] = tally(utstring_body(tmp[1]));
	    if (d[0] == d[1]) {				/* only if equal */
		arityterm(cur->next->u.lis, str);	/* TRUE branch */
		cur = cur->next->next->next;
	    } else
		arityfactor(cur, str);
	} else
	    arityfactor(cur, str);
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
