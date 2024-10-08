/*
    module  : small.c
    version : 1.14
    date    : 09/17/24
*/
#ifndef SMALL_C
#define SMALL_C

/**
Q0  OK  2210  small  :  DA  X  ->  B
Tests whether aggregate X has 0 or 1 members, or numeric 0 or 1.
*/
void small_(pEnv env)
{
    int i = 0;
    Node node;

    PARM(1, SMALL);
    node = vec_pop(env->stck);
    switch (node.op) {
#if 0
    case USR_:
    case USR_PRIME_:
	node.u.num = node.u.ent < 2;
	break;
    case ANON_FUNCT_:
    case ANON_PRIME_:
	node.u.num = !node.u.proc;
	break;
#endif
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
	node.u.num = !node.u.num || node.u.num == 1;
	break;
    case SET_:
	if (node.u.set) {
	    while (!(node.u.set & ((int64_t)1 << i)))
		i++;
	    node.u.num = (node.u.set & ~((int64_t)1 << i)) == 0;
	} else
	    node.u.num = 1;
	break;
    case STRING_:
    case USR_STRING_:
	node.u.num = strlen(node.u.str) < 2;
	break;
    case LIST_:
    case USR_LIST_:
	node.u.num = vec_size(node.u.lis) < 2;
	break;
#if 0
    case FLOAT_:
	node.u.num = node.u.dbl >= 0 && node.u.dbl < 2;
	break;
    case FILE_:
	node.u.num = !node.u.fil || (node.u.fil - stdin) < 2;
	break;
#endif
#ifdef USE_BIGNUM_ARITHMETIC
    case BIGNUM_:
	node.u.num = node.u.str[1] == '0' || !strcmp(node.u.str, " 1");
	break;
#endif
    default:
	node.u.num = 0;		/* false */
	break;
    }
    node.op = BOOLEAN_;
    vec_push(env->stck, node);
}
#endif
