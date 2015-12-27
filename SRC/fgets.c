/* fgets.c */
PRIVATE void fgets_()
{
    int length = 0;
    int size = INPLINEMAX;
    char *buf = 0;

    ONEPARAM("fgets");
    FILE("fgets");
    buf = GC_malloc(size);
    buf[0] = 0;
    while (fgets(buf + length, size - length, stk->u.fil)) {
	if ((length = strlen(buf)) > 0 && buf[length - 1] == '\n')
	    break;
	buf = GC_realloc(buf, size <<= 1);
    }
    PUSH(STRING_, GC_strdup(buf));
}
