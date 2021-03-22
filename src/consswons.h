/*
    module  : consswons.h
    version : 1.12
    date    : 03/15/21
*/
PRIVATE void PROCEDURE(pEnv env)
{
    char *str;

#ifndef OLD_RUNTIME
    if (compiling && VALID_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS(NAME);
    switch (AGGR->op) {
    case LIST_:
	env->stk->next->u.lis = newnode(ELEM->op, ELEM->u, AGGR->u.lis);
	env->stk->next->op = LIST_;
	POP(env->stk);
	break;
    case STRING_:
#ifndef NCHECK
	if (ELEM->op != CHAR_)
	    execerror("character", NAME);
#endif
	str = GC_malloc_atomic(strlen(AGGR->u.str) + 2);
	str[0] = (char)ELEM->u.num;
	strcpy(str + 1, AGGR->u.str);
	env->stk->next->u.str = str;
	env->stk->next->op = STRING_;
	POP(env->stk);
	break;
    case SET_:
	CHECKSETMEMBER(ELEM, NAME);
	env->stk->next->u.set = AGGR->u.set | ((long_t)1 << ELEM->u.num);
	env->stk->next->op = SET_;
	POP(env->stk);
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
