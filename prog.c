/*
    module  : prog.c
    version : 1.7
    date    : 10/02/23
*/
#include "globals.h"

/*
    prog - push the contents of a program onto the code stack
*/
PUBLIC void prog(pEnv env, NodeList *list)
{
    int i, j;

    for (i = 0, j = pvec_cnt(list); i < j; i++)
	env->prog = pvec_add(env->prog, pvec_nth(list, i));
}

/*
    code - push an anonymous function onto the code stack
*/
PUBLIC void code(pEnv env, proc_t proc)
{
    Node node;

    node.u.proc = proc;
    node.op = ANON_FUNCT_;
    env->prog = pvec_add(env->prog, node);
}

/*
    push - push an integer on the code stack
*/
PUBLIC void push(pEnv env, int64_t num)
{
    Node node;

    node.u.num = num;
    node.op = INTEGER_;
    env->prog = pvec_add(env->prog, node);
}

/*
    prime - push node on the code stack that came from the data stack
*/
PUBLIC void prime(pEnv env, Node node)
{
    if (node.op == USR_)
	node.op = USR_PRIME_;
    if (node.op == ANON_FUNCT_)
	node.op = ANON_PRIME_;
    env->prog = pvec_add(env->prog, node);
}

/*
    pop - remove an item from the code stack
*/
PUBLIC Node pop(pEnv env)
{
    Node node;

    env->prog = pvec_pop(env->prog, &node);
    return node;
}
