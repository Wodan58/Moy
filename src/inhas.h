/*
    module  : inhas.h
    version : 1.12
    date    : 06/20/22
*/
#include "compare.h"

PRIVATE void PROCEDURE(pEnv env)
{
    Node *cur;
    char *str;
    int found = 0;

    TWOPARAMS(NAME);
    switch (AGGR->op) {
    case LIST_:
	for (cur = AGGR->u.lis; cur; cur = cur->next)
	    if (!Compare(env, cur, ELEM))
		break;
	found = cur != 0;
	break;
    case STRING_:
	for (str = AGGR->u.str; *str && *str != ELEM->u.num; str++)
	    ;
	found = *str != 0;
	break;
    case SET_:
	found = (AGGR->u.set & ((long)1 << ELEM->u.num)) > 0;
	break;
    default:
	BADAGGREGATE(NAME);
	break;
    }
    BINARY(BOOLEAN_NEWNODE, found);
}

#undef PROCEDURE
#undef NAME
#undef AGGR
#undef ELEM
