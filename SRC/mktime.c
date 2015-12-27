/* mktime.c */
PRIVATE void mktime_()
{
    struct tm t;

    ONEPARAM("mktime");
    LIST("mktime");
    decode_time(&t);
    if (OUTSIDE) {
	stk->u.num = mktime(&t);
	stk->op = INTEGER_;
    } else
	UNARY(INTEGER_NEWNODE, mktime(&t));
}
