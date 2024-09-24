/*
    module  : assign.c
    version : 1.5
    date    : 09/17/24
*/
#ifndef ASSIGN_C
#define ASSIGN_C

/**
Q0  IGNORE_POP  3140  assign  :  DD  V [N]  ->
[IMPURE] Assigns value V to the variable with name N.
*/
void assign_(pEnv env)
{
    Node node;
    int index;
    Entry ent;

    PARM(2, ASSIGN);			/* quotation on top */
    node = vec_pop(env->stck);		/* singleton list */
    node = vec_back(node.u.lis);	/* first/last element */
    index = node.u.ent;			/* index user defined name */
    ent = vec_at(env->symtab, index);	/* symbol table entry */
    node = vec_pop(env->stck);		/* read value */
    ent.is_user = 1;			/* ensure again user defined */
    vec_init(ent.u.body);		/* (re)initialise body */
    vec_push(ent.u.body, node);		/* insert value in body */
    vec_at(env->symtab, index) = ent;	/* update symbol table */
}
#endif
