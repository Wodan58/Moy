/*
    module  : assign.c
    version : 1.3
    date    : 03/21/24
*/
#ifndef ASSIGN_C
#define ASSIGN_C

/**
Q0  IGNORE_POP  3190  assign  :  DD  V [N]  ->
[IMPURE] Assigns value V to the variable with name N.
*/
void assign_(pEnv env)
{
    Node node;
    int index;
    Entry ent;

    PARM(2, ASSIGN);				/* quotation on top */
    env->stck = pvec_pop(env->stck, &node);	/* singleton list */
    node = pvec_lst(node.u.lis);		/* first/last element */
    index = node.u.ent;				/* index user defined name */
    ent = vec_at(env->symtab, index);		/* symbol table entry */
    env->stck = pvec_pop(env->stck, &node);	/* value */
    ent.is_user = 1;				/* ensure again user defined */
    ent.u.body = pvec_init();			/* (re)initialise body */
    ent.u.body = pvec_add(ent.u.body, node);	/* insert value in body */
    vec_at(env->symtab, index) = ent;		/* update symbol table */
}
#endif
