/*
    module  : primrec.c
    version : 1.10
    date    : 03/05/24
*/
#ifndef PRIMREC_C
#define PRIMREC_C

/**
Q2  OK  2820  primrec  :  DDDA  X [I] [C]  ->  R
Executes I to obtain an initial value R0.
For integer X uses increasing positive integers to X, combines by C for new R.
For aggregate X uses successive members and combines by C for new R.
*/
void primrec_(pEnv env)
{
    int64_t i, j, k = 0;
    Node first, second, third, node;

    PARM(3, PRIMREC);
    env->stck = pvec_pop(env->stck, &third);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    switch (first.op) {
    case LIST_:
	k = pvec_cnt(first.u.lis);
	for (i = k - 1; i >= 0; i--)
	    env->stck = pvec_add(env->stck, pvec_nth(first.u.lis, i));
	break;
 
    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	node.op = CHAR_;
	k = strlen(first.u.str);
	for (i = 0; i < k; i++) {
	    node.u.num = first.u.str[i];
	    env->stck = pvec_add(env->stck, node);
	}
	break;

    case SET_:
	node.op = INTEGER_;
	for (k = 0, j = 1, i = 0; i < SETSIZE; i++, j <<= 1)
	    if (first.u.set & j) {
		node.u.num = i;
		env->stck = pvec_add(env->stck, node);
		k++;
	    }
	break;
 
    case INTEGER_:
	node.op = INTEGER_;
	for (k = i = first.u.num; i > 0; i--) {
	    node.u.num = i;
	    env->stck = pvec_add(env->stck, node);
	}
	break;
    }
    for (i = 0; i < k; i++)
	prog(env, third.u.lis);
    prog(env, second.u.lis);
}
#endif
