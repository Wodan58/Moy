/*
    module  : prog.c
    version : 1.6
    date    : 09/04/23
*/
#include "globals.h"

/*
    prog - push the contents of a program onto the code stack
*/
PUBLIC void prog(pEnv env, NodeList *list)
{
    int i, j;
    Node node;

    for (i = 0, j = lst_size(list); i < j; i++) {
	node = lst_at(list, i);
	lst_push(env->prog, node);
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
    lst_push(env->prog, node);
}

/*
    push - push an integer on the code stack
*/
PUBLIC void push(pEnv env, int64_t num)
{
    Node node;

    node.u.num = num;
    node.op = INTEGER_;
    lst_push(env->prog, node);
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
    lst_push(env->prog, node);
}

/*
    pop - remove an item from the code stack
*/
PUBLIC Node pop(pEnv env)
{
    return lst_pop(env->prog);
}
