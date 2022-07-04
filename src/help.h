/*
    module  : help.h
    version : 1.10
    date    : 06/20/22
*/
PRIVATE void PROCEDURE(pEnv env)
{
#ifdef COMPILING
    char *ptr;
    Node node;
    int i, column = 0, leng;

    COMPILE;
    for (i = dict_size(env) - 1; i >= 0; i--) {
	node.u.num = i;
	ptr = dict_descr(env, &node);
	if (*ptr REL '_' && !isdigit(*ptr)) {
	    leng = strlen(ptr) + 1;
	    if (column + leng > LINEWIDTH) {
		putchar('\n');
		column = 0;
	    }
	    printf("%s ", ptr);
	    column += leng;
	}
    }
    putchar('\n');
#endif
}

#undef PROCEDURE
#undef REL
