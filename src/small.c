/*
    module  : small.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef SMALL_C
#define SMALL_C

/**
OK 2220  small  :  DA	X  ->  B
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
    case USR_PRIME_:
    case USR_:
        node.u.num = node.u.ent < 2;
        break;
    case ANON_PRIME_:
    case ANON_FUNCT_:
        node.u.num = !node.u.proc;
        break;
#endif
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
        node.u.num = node.u.num < 2;
        break;
    case SET_:
        if (node.u.set) {
            while (!(node.u.set & ((long)1 << i)))
                i++;
            node.u.num = (node.u.set & ~((long)1 << i)) == 0;
        } else
            node.u.num = 1;
        break;
    case STRING_:
        node.u.num = strlen(node.u.str) < 2;
        break;
    case LIST_:
        node.u.num = vec_size(node.u.lis) < 2;
        break;
#if 0
    case FLOAT_:
        node.u.num = node.u.dbl >= 0 && node.u.dbl < 2;
        break;
    case FILE_:
        node.u.num = (node.u.fil - stdin) < 2;
        break;
#endif
    }
    node.op = BOOLEAN_;
    vec_push(env->stck, node);
}
#endif
