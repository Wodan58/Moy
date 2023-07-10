/*
    module  : fpush.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef FPUSH_C
#define FPUSH_C

/**
OK 3320  (fpush)  :  D	->
Pop the location of an aggregate and an element from the program stack.
If the top of the data stack is true, add the element to the aggregate.
*/
void fpush_(pEnv env)
{
    int i;
    Node test, jump, elem, node;

    PARM(1, ANYTYPE);
    test = vec_pop(env->stck);
    jump = vec_pop(env->prog);
    elem = vec_pop(env->prog);
    if (test.u.num) {
        node = vec_at(env->prog, jump.u.num);
        switch (node.op) {
        case LIST_:
            vec_push(node.u.lis, elem);
            break;

        case STRING_:
            i = strlen(node.u.str);
            node.u.str[i++] = elem.u.num;
            node.u.str[i] = 0;
            break;

        case SET_:
            node.u.set |= ((long)1 << elem.u.num);
        default:
            break;
        }
        vec_assign(env->prog, jump.u.num, node); /* write node */
    }
}
#endif
