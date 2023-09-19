/*
    module  : null.c
    version : 1.7
    date    : 09/18/23
*/
#ifndef NULL_C
#define NULL_C

/**
OK 2200  null  :  DA	X  ->  B
Tests for empty aggregate X or zero numeric.
*/
void null_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    node = lst_pop(env->stck);
    switch (node.op) {
    case USR_:
    case USR_PRIME_:
	node.u.num = !node.u.ent;
	break;
    case ANON_FUNCT_:
    case ANON_PRIME_:
	node.u.num = !node.u.proc;
	break;
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
	node.u.num = !node.u.num;
	break;
    case SET_:
	node.u.num = !node.u.set;
	break;
    case STRING_:
    case USR_STRING_:
	node.u.num = !*node.u.str;
	break;
    case LIST_:
    case USR_LIST_:
	node.u.num = !lst_size(node.u.lis);
	break;
    case FLOAT_:
	node.u.num = !node.u.dbl;
	break;
    case FILE_:
	node.u.num = !node.u.fil;
	break;
    case BIGNUM_:
	node.u.num = node.u.str[1] == '0';
	break;
    }
    node.op = BOOLEAN_;
    lst_push(env->stck, node);
}
#endif
