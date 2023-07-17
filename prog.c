/*
    module  : prog.c
    version : 1.3
    date    : 07/17/23
*/
#include "globals.h"

/*
    prog - push the contents of a program onto the code stack
*/
PUBLIC void prog(pEnv env, NodeList *list)
{
    int i, j;
    Node node;

    for (i = 0, j = vec_size(list); i < j; i++) {
        node = vec_at(list, i);
        vec_push(env->prog, node);
    }
}

/*
    code - push an anonymous function onto the code stack
*/
PUBLIC void code(pEnv env, proc_t proc)
{
    Node node;

    node.u.proc = proc;
    node.op = ANON_FUNCT_;
    vec_push(env->prog, node);
}

/*
    push - push an integer on the code stack
*/
PUBLIC void push(pEnv env, int64_t num)
{
    Node node;

    node.u.num = num;
    node.op = INTEGER_;
    vec_push(env->prog, node);
}

/*
    prime - push node on the code stack that came from the data stack
*/
PUBLIC void prime(pEnv env, Node node)
{
    if (node.op == USR_ || node.op == ANON_FUNCT_)
        node.op += 10;
    vec_push(env->prog, node);
}

/*
    pop - remove an item from the code stack
*/
PUBLIC Node pop(pEnv env)
{
    return vec_pop(env->prog);
}
