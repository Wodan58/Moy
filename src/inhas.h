/*
    module  : inhas.h
    version : 1.11
    date    : 03/15/21
*/
PRIVATE void PROCEDURE(pEnv env)
{
    Node *cur;
    char *str;
    int found = 0;
#ifdef CORRECT_INHAS_COMPARE
    int ok;
#endif

#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS(NAME);
    switch (AGGR->op) {
    case LIST_:
	for (cur = AGGR->u.lis; cur; cur = cur->next)
#ifdef CORRECT_INHAS_COMPARE
	    if (Compare(env, cur, ELEM, &ok) == ok)
#else
	    if (cur->u.num == ELEM->u.num)
#endif
		break;
	found = cur != 0;
	break;
    case STRING_:
	for (str = AGGR->u.str; *str && *str != ELEM->u.num; str++)
	    ;
	found = *str != 0;
	break;
    case SET_:
	found = (AGGR->u.set & ((long_t)1 << ELEM->u.num)) > 0;
	break;
    default:
	BADAGGREGATE(NAME);
	break;
    }
    env->stk->next->u.num = found;
    env->stk->next->op = BOOLEAN_;
    POP(env->stk);
}

#undef PROCEDURE
#undef NAME
#undef AGGR
#undef ELEM
