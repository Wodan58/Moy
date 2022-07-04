/*
    module  : cons_swons.h
    version : 1.13
    date    : 06/20/22
*/
PRIVATE void PROCEDURE(pEnv env)
{
    char *str;

    TWOPARAMS(NAME);
    switch (AGGR->op) {
    case LIST_:
	BINARY(LIST_NEWNODE, newnode(ELEM->op, ELEM->u, AGGR->u.lis));
	break;
    case STRING_:
	CHECKCHARACTER(ELEM, NAME);
	str = GC_malloc_atomic(strlen(AGGR->u.str) + 2);
	str[0] = (char)ELEM->u.num;
	strcpy(str + 1, AGGR->u.str);
	BINARY(STRING_NEWNODE, str);
	break;
    case SET_:
	CHECKSETMEMBER(ELEM, NAME);
	BINARY(SET_NEWNODE, AGGR->u.set | ((long)1 << ELEM->u.num));
	break;
    default:
	BADAGGREGATE(NAME);
	break;
    }
}

#undef PROCEDURE
#undef NAME
#undef AGGR
#undef ELEM
