/*
    module  : fpush.c
    version : 1.6
    date    : 09/11/23
*/
#ifndef FPUSH_C
#define FPUSH_C

/**
OK 3380  (fpush)  :  D	->
Pop the location of an aggregate and an element from the program stack.
If the top of the data stack is true, add the element to the aggregate.
*/
void fpush_(pEnv env)
{
#ifndef COMPILER
    int i;
    Node test, jump, elem, node;

    PARM(1, ANYTYPE);
    test = lst_pop(env->stck);
    jump = lst_pop(env->prog);
    elem = lst_pop(env->prog);
    if (test.u.num) {
	node = lst_at(env->prog, jump.u.num);
	switch (node.op) {
	case LIST_:
	    lst_push(node.u.lis, elem);
	    break;

	case STRING_:
	case BIGNUM_:
	    i = strlen(node.u.str);
	    node.u.str[i++] = elem.u.num;
	    node.u.str[i] = 0;
	    break;

	case SET_:
	    node.u.set |= ((int64_t)1 << elem.u.num);
	default:
	    break;
	}
	lst_assign(env->prog, jump.u.num, node); /* write node */
    }
#endif
}
#endif
