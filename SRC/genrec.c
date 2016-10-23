/*
    module  : genrec.c
    version : 1.6
    date    : 10/16/16
*/
#include "interp.h"

/*
genrec  :  [B] [T] [R1] [R2]  ->  ...
Executes B, if that yields true, executes T.
Else executes R1 and then [[[B] [T] [R1] R2] genrec] R2.
*/
/* genrec.c */
PRIVATE void genrecaux(void)
{
    int num;
    Node temp, *prog, *save;

    temp = *stk;
    prog = stk->u.lis->u.lis;
    POP(stk);
    save = stk;
#ifdef ARITY
    copy_(arity(prog));
#else
    CONDITION;
#endif
    exeterm(prog);
    num = stk->u.num;
    stk = save;
#ifndef ARITY
    RELEASE;
#endif
    if (num)
	exeterm(temp.u.lis->next->u.lis);
    else {
	exeterm(temp.u.lis->next->next->u.lis);
	PUSH(LIST_, temp.u.lis);
	NULLARY(LIST_NEWNODE, ANON_FUNCT_NEWNODE(genrecaux, 0));
	cons_();
	exeterm(temp.u.lis->next->next->next);
    }
}

PRIVATE void genrec_(void)
{
    FOURPARAMS("genrec");
    FOURQUOTES("genrec");
    cons_();
    cons_();
    cons_();
    genrecaux();
}
