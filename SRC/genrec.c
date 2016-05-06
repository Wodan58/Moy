/*
    module  : genrec.c
    version : 1.2
    date    : 05/06/16
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
    Node buf, *prog, *save;

    buf = *stk;
    prog = &buf;
    POP(stk);
    save = stk;
    CONDITION;
    exeterm(prog->u.lis->u.lis);
    num = stk->u.num;
    RELEASE;
    stk = save;
    if (num)
	exeterm(prog->u.lis->next->u.lis);
    else {
	exeterm(prog->u.lis->next->next->u.lis);
	PUSH(LIST_, prog->u.lis);
	PUSH(LIST_, ANON_FUNCT_NEWNODE(genrecaux, 0));
	cons_();
	exeterm(prog->u.lis->next->next->next);
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
