/*
    module  : arty.c
    version : 1.6
    date    : 11/06/23
*/
#include "globals.h"

/*
    Check the arity of a quotation. Parameter num is the initial value.
    The desired outcome is 1. In case of an error -1 is returned.
    The rules are that num cannot become negative and that unknown effects
    are handled by returning -1. Unknown only means that it is considered
    too difficult to try to figure out what the stack effect is.
*/
PUBLIC int arity(pEnv env, NodeList *quot, int num)
{
    char *str;
    Entry ent;
    NodeList *list;
    Node node, prev;

    list = pvec_init();
    pvec_copy(list, quot);			/* make a copy */
    prev.u.lis = 0;
    prev.op = 0;
    while (pvec_cnt(list)) {
	list = pvec_pop(list, &node);		/* read a node */
	switch (node.op) {
	case USR_:
	    ent = vec_at(env->symtab, node.u.ent);
	    if (ent.u.body && !pvec_getused(ent.u.body)) {
		list = pvec_concat(list, ent.u.body);
		pvec_setused(ent.u.body);	/* prevent recursion */
	    }
	    break;
	case ANON_FUNCT_:
	    str = operarity(node.u.proc);	/* problem: lineair search */
	    for (; *str; str++)
		if (*str == 'A')		/* add */
		    num++;
		else if (*str == 'D') {		/* delete */
		    if (--num < 0)
			return -1;
		} else if (*str == 'P') {	/* previous */
		    if (prev.op != LIST_)
			return -1;
		    list = pvec_concat(list, prev.u.lis);
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
	prev = node;
    }
    return num;
}
