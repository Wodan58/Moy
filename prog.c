/*
    module  : prog.c
    version : 1.12
    date    : 09/17/24
*/
#include "globals.h"

/*
 * prog - push the contents of a program onto the code stack
 */
void prog(pEnv env, NodeList list)
{
    int i, j;

    for (i = 0, j = vec_size(list); i < j; i++)
	vec_push(env->prog, vec_at(list, i));
}

/*
 * code pushes an anonymous function onto the code stack.
 */
void code(pEnv env, proc_t proc)
{
    Node node;

    node.u.proc = proc;
    node.op = ANON_FUNCT_;
    vec_push(env->prog, node);
}

/*
 * push an integer on the code stack.
 */
void push(pEnv env, int64_t num)
{
    Node node;

    node.u.num = num;
    node.op = INTEGER_;
    vec_push(env->prog, node);
}

/*
 * prime pushes a node on the code stack that came from the data stack.
 */
void prime(pEnv env, Node node)
{
    if (node.op == USR_)
	node.op = USR_PRIME_;
    if (node.op == ANON_FUNCT_)
	node.op = ANON_PRIME_;
    vec_push(env->prog, node);
}

/*
 * pop - remove an item from the code stack
 */
Node pop(pEnv env)
{
    return vec_pop(env->prog);
}
