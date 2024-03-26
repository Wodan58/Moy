/*
    module  : arty.c
    version : 1.13
    date    : 03/21/24
*/
#include "globals.h"

/*
    Check the arity of a quotation. Parameter num is the initial value.
    The desired outcome is 1. In case of an error -1 is returned.
    The rules are that num cannot become negative and that unknown effects
    are handled by returning -1. Unknown only means that it is considered
    too difficult to try to figure out what the stack effect is.
*/
static int aggr_size(Node node)
{
    int num;
    int64_t i, j;

    switch (node.op) {
    case LIST_:
	return pvec_cnt(node.u.lis);

    case BIGNUM_:
    case STRING_:
	return strlen(node.u.str);

    case SET_:
	for (num = 0, j = 1, i = 0; i < SETSIZE; i++, j <<= 1)
	    if (node.u.set & j)
		num++;
	return num;
    }
    return 0;
}

int arity(pEnv env, NodeList *quot, int num)
{
    char *str;
    int aggr, prog;				/* step combinator */
    NodeList *list;
    Node node, prev, prevprev;

    list = pvec_init();
    pvec_copy(list, quot);			/* make a copy */
    prevprev.u.lis = prev.u.lis = 0;
    prevprev.op = prev.op = 0;
    while (pvec_cnt(list)) {
	list = pvec_pop(list, &node);		/* read a node */
	switch (node.op) {
	case USR_:
	    return -1;				/* assume too difficult */
	case ANON_FUNCT_:
	    if (env->bytecoding || env->compiling)
		str = operarity(node.u.ent);
	    else
		str = operarity(operindex(env, node.u.proc));
	    for (; *str; str++)
		if (*str == 'A')		/* add */
		    num++;
		else if (*str == 'D') {		/* delete */
		    if (--num < 0)
			return -1;
		} else if (*str == 'P') {	/* previous one */
		    if (prev.op != LIST_)
			return -1;
		    if (prev.u.lis) {		/* skip empty */
			prog = arity(env, prev.u.lis, 0);	/* recursion */
			if (prog < 0)
			    return -1;
			num += prog;
		    }
		} else if (*str == 'Q') {	/* previous two */
		    if (prev.op != LIST_)
			return -1;
		    if ((prog = arity(env, prev.u.lis, 1)) < 0)	/* recursion */
			return -1;
		    aggr = aggr_size(prevprev);	/* size of aggregate */
		    num += aggr * prog;
		} else if (*str == 'U')		/* unknown */
		    return -1;
	    break;
	case USR_PRIME_:
	case ANON_PRIME_:
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	case STRING_:
	case LIST_:
	case FLOAT_:
	case FILE_:
	case BIGNUM_:
	    num++;
	    break;
	}
	prevprev = prev;
	prev = node;
    }
    return num;
}
