/* while.c */
PRIVATE void while_()
{
    int num;
    Node *body, *test, *save;

    TWOPARAMS("while");
    TWOQUOTES("while");
    body = stk->u.lis;
    POP(stk);
    test = stk->u.lis;
    POP(stk);
    for (;;) {
	save = stk;

	inside_critical++;
	exeterm(test);
	num = stk->u.num;
	if (--inside_critical == 0)
	    tmp_release();

	stk = save;
	if (!num)
	    return;
	exeterm(body);
    }
}
