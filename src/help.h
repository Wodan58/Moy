/*
    module  : help.h
    version : 1.3
    date    : 03/12/17
*/
#define LINEWIDTH	72

PRIVATE void PROCEDURE(void)
{
    char *ptr;
    int i, column = 0, leng;

#ifndef NCHECK
    COMPILE;
#endif
    for (i = symtabindex - 1; i >= 0; i--)
	if (symtab[i].name[0] REL '_' && (symtab[i].flags & IS_LOCAL) == 0) {
	    ptr = symtab[i].name;
	    leng = strlen(ptr) + 1;
	    if (column + leng > LINEWIDTH) {
		printf("\n");
		column = 0;
	    }
	    printf("%s", ptr);
	    putchar(' ');
	    column += leng;
	}
    putchar('\n');
}

#undef PROCEDURE
#undef REL
#undef LINEWIDTH
