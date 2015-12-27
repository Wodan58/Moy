/* genrec.c */
PRIVATE void genrecaux()
{
    int num;
    Node prog, *save;

    prog = *stk;
    POP(stk);
    save = stk;

    inside_critical++;
    exeterm(prog.u.lis->u.lis);
    num = stk->u.num;
    if (--inside_critical == 0)
	tmp_release();

    stk = save;
    if (num)
	exeterm(prog.u.lis->next->u.lis);
    else {
	exeterm(prog.u.lis->next->next->u.lis);
	PUSH(LIST_, prog.u.lis);
	PUSH(LIST_, ANON_FUNCT_NEWNODE(genrecaux, 0));
	cons_();
	exeterm(prog.u.lis->next->next->next);
    }
}

PRIVATE void genrec_()
{
    FOURPARAMS("genrec");
    FOURQUOTES("genrec");
    cons_();
    cons_();
    cons_();
    genrecaux();
}
