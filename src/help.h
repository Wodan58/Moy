/*
    module  : help.h
    version : 1.4
    date    : 06/28/18
*/
#define LINEWIDTH	72

PRIVATE void PROCEDURE(void)
{
#ifndef NCHECK
    char *ptr;
    int i, column = 0, leng;

    COMPILE;
    for (i = dict_size() - 1; i >= 0; i--) {
	ptr = dict_descr(i);
	if (*ptr REL '_' && (dict_flags(i) & IS_LOCAL) == 0) {
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
#undef LINEWIDTH
