/*
    module  : null.c
    version : 1.12
    date    : 04/11/24
*/
#ifndef NULL_C
#define NULL_C

/**
Q0  OK  2200  null  :  DA  X  ->  B
Tests for empty aggregate X or zero numeric.
*/
void null_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    env->stck = pvec_pop(env->stck, &node);
    switch (node.op) {
#if 0
    case USR_:
    case USR_PRIME_:
	node.u.num = !node.u.ent;
	break;
    case ANON_FUNCT_:
    case ANON_PRIME_:
	node.u.num = !node.u.proc;
	break;
#endif
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
	node.u.num = !pvec_cnt(node.u.lis);
	break;
    case FLOAT_:
	node.u.num = !node.u.dbl;
	break;
    case FILE_:
	node.u.num = !node.u.fil;
	break;
#ifdef USE_BIGNUM_ARITHMETIC
    case BIGNUM_:
	node.u.num = node.u.str[1] == '0';
	break;
#endif
    default:
	node.u.num = 0;		/* false */
	break;
    }
    node.op = BOOLEAN_;
    env->stck = pvec_add(env->stck, node);
}
#endif
