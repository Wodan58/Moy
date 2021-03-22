/*
    module  : help.h
    version : 1.9
    date    : 03/15/21
*/
PRIVATE void PROCEDURE(pEnv env)
{
#ifndef OLD_RUNTIME
    char *ptr;
    int i, column = 0, leng;

    COMPILE;
    for (i = dict_size(env) - 1; i >= 0; i--) {
	ptr = dict_descr(env, i);
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
