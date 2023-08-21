/*
    module  : arty.c
    version : 1.3
    date    : 08/21/23
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
    Node node, prev;
    NodeList *list = 0;
    int i, j = vec_size(quot);

    if (j)
	vec_init(list);
    for (i = 0; i < j; i++) {
	node = vec_at(quot, i);
	vec_push(list, node);
    }
    prev.op = 0;
    prev.u.lis = 0;
    while (vec_size(list)) {
	node = vec_pop(list);
	switch (node.op) {
	case USR_:
	    ent = sym_at(env->symtab, node.u.ent);
	    if (ent.u.body && !vec_used(ent.u.body)) {
		for (i = 0, j = vec_size(ent.u.body); i < j; i++) {
		    node = vec_at(ent.u.body, i);
		    vec_push(list, node);
		}
		vec_setused(ent.u.body);
	    }
	    break;
	case ANON_FUNCT_:
	    str = operarity(node.u.proc); /* problem: lineair search */
	    for (; *str; str++)
		if (*str == 'A') /* add */
		    num++;
		else if (*str == 'D') { /* delete */
		    if (--num < 0)
			return -1;
		} else if (*str == 'P') { /* previous */
		    if (prev.op == LIST_) {
			for (i = 0, j = vec_size(prev.u.lis); i < j; i++) {
			    node = vec_at(prev.u.lis, i);
			    vec_push(list, node);
			}
			break;
		    }
		    return -1;
		} else if (*str == 'U') /* unknown */
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
