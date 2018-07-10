/*
    module  : help.h
    version : 1.6
    date    : 07/10/18
*/
PRIVATE void PROCEDURE(void)
{
#ifndef NCHECK
    char *ptr;
    int i, column = 0, leng;

    COMPILE;
    for (i = dict_size() - 1; i >= 0; i--) {
	ptr = dict_descr(i);
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
