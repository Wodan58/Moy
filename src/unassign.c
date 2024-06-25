/*
    module  : unassign.c
    version : 1.2
    date    : 06/22/24
*/
#ifndef UNASSIGN_C
#define UNASSIGN_C

/**
Q0  IGNORE_POP  3230  unassign  :  D  [N]  ->
[IMPURE] Sets the body of the name N to uninitialized.
*/
void unassign_(pEnv env)
{
    Node node;
    int index;
    Entry ent;

    PARM(1, ASSIGN);				/* quotation on top */
    env->stck = pvec_pop(env->stck, &node);	/* singleton list */
    node = pvec_lst(node.u.lis);		/* first/last element */
    index = node.u.ent;				/* index user defined name */
    ent = vec_at(env->symtab, index);		/* symbol table entry */
    ent.is_user = 1;				/* ensure again user defined */
    ent.u.body = 0;				/* (re)initialise body */
    vec_at(env->symtab, index) = ent;		/* update symbol table */
}
#endif
