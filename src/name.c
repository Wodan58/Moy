/*
    module  : name.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef NAME_C
#define NAME_C

/**
OK 2180  name  :  DA	sym  ->  "sym"
For operators and combinators, the string "sym" is the name of item sym,
for literals sym the result string is its type.
*/
void name_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    node = vec_pop(env->stck);
    if (node.op == USR_)
        node.u.str = sym_at(env->symtab, node.u.ent).name;
    else if (node.op == ANON_FUNCT_)
        node.u.str = printname(node.u.proc);
    else
        node.u.str = showname(node.op);
    node.op = STRING_;
    vec_push(env->stck, node);
}
#endif
