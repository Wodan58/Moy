/*
    module  : arity.c
    version : 1.9
    date    : 06/28/18
*/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "runtime.h"
#include "vector.h"

#define P(x)	PrintString(str, x)

/* declare vector type */
typedef vector(char) String;

char *aritysym(int op);
static void arityterm(Node *cur, String *str);

static void PrintString(String *str, char *tmp)
{
    char *ptr;

    while (*tmp) {
	ptr = vec_push(str);
	*ptr = *tmp++;
    }
}

static void arityfactor(Node *cur, String *str)
{
    int index;
    unsigned flags;

    switch (cur->op) {
    case USR_:
	index = cur->u.num;
	flags = dict_flags(index);
	if ((flags & IS_MARKED) == 0) {
	    dict_setflags(index, flags | IS_MARKED);
	    arityterm(dict_body(index), str);
	    dict_setflags(index, flags);
	}
	break;
    default:
	PrintString(str, aritysym(cur->op));
	break;
    }
}

static int tally(char *str)
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

static void arityterm(Node *cur, String *str)
{
    for (; cur; cur = cur->next)
	arityfactor(cur, str);
}

int arity(Node *cur)
{
    int num;
    char *ptr;
    String *str;

    vec_init(str);
    arityterm(cur, str);
    ptr = vec_index(str, 0);
    num = tally(ptr);
    return num;
}
