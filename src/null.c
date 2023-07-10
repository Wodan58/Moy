/*
    module  : null.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef NULL_C
#define NULL_C

/**
OK 2210  null  :  DA	X  ->  B
Tests for empty aggregate X or zero numeric.
*/
void null_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    node = vec_pop(env->stck);
    switch (node.op) {
    case USR_PRIME_:
    case USR_:
        node.u.num = !node.u.ent;
        break;
    case ANON_PRIME_:
    case ANON_FUNCT_:
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
        node.u.num = !*node.u.str;
        break;
    case LIST_:
        node.u.num = !vec_size(node.u.lis);
        break;
    case FLOAT_:
        node.u.num = !node.u.dbl;
        break;
    case FILE_:
        node.u.num = !node.u.fil;
        break;
    }
    node.op = BOOLEAN_;
    vec_push(env->stck, node);
}
#endif
