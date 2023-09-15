/*
    module  : primrec.c
    version : 1.7
    date    : 09/15/23
*/
#ifndef PRIMREC_C
#define PRIMREC_C

/**
OK 2820  primrec  :  DDDA	X [I] [C]  ->  R
Executes I to obtain an initial value R0.
For integer X uses increasing positive integers to X, combines by C for new R.
For aggregate X uses successive members and combines by C for new R.
*/
void primrec_(pEnv env)
{
    char *str;
    int i, j = 0;
    Node first, second, third, node;

    PARM(3, PRIMREC);
    third = lst_pop(env->stck);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    switch (first.op) {
    case LIST_:
	j = lst_size(first.u.lis);
	for (i = j - 1; i >= 0; i--) {
	    node = lst_at(first.u.lis, i);
	    lst_push(env->stck, node);
	}
	break;
 
    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	node.op = CHAR_;
	j = strlen(first.u.str);
	for (str = first.u.str; *str; str++) {
	    node.u.num = *str;
	    lst_push(env->stck, node);
	}
	break;

    case SET_:
	node.op = INTEGER_;
	for (j = i = 0; i < SETSIZE; i++)
	    if (first.u.set & ((int64_t)1 << i)) {
		node.u.num = i;
		lst_push(env->stck, node);
		j++;
	    }
	break;
 
    case INTEGER_:
	node.op = INTEGER_;
	for (j = i = first.u.num; i > 0; i--) {
	    node.u.num = i;
	    lst_push(env->stck, node);
	}
	break;

    default:
	break;
    }
    for (i = 0; i < j; i++)
	prog(env, third.u.lis);
    prog(env, second.u.lis);
}
#endif
