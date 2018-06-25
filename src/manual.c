/*
    module  : manual.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

#define PLAIN (style == 0)
#define HTML  (style == 1)
#define LATEX (style == 2)

#define HEADER(N,NAME,HEAD)					\
    if (strcmp(N,NAME) == 0) {					\
	printf("\n\n");						\
	if (HTML) printf("<DT><BR><B>");			\
	if (LATEX) printf("\\item[--- \\BX{");			\
	printf("%s",HEAD);					\
	if (LATEX) printf("} ---] \\verb# #");			\
	if (HTML) printf("</B><BR><BR>");			\
	printf("\n\n"); }

extern optable_t optable[];

PRIVATE void make_manual(int style /* 0=plain, 1=HTML, 2=Latex */)
{
    char *name;
    int i, j = 0;

    if (HTML)
	printf("<HTML>\n<DL>\n");
    for (i = 0; (name = optable[i].name) != 0; i++) {
	HEADER(name, " truth value type", "literal");
	if (!j && isspace(name[0]))
	    j = 1;
	else if (j == 1 && !isspace(name[0])) {
	    j = 2;
	    HEADER(name, name, "operator");
	}
#if 0
	HEADER(name, "nothing", "operand") else
	HEADER(name, "id", "operator") else
	HEADER(name, "null", "predicate") else
	HEADER(name, "i", "combinator") else
	HEADER(name, "help", "miscellaneous commands")
#endif
	if (name[0] != '_') {
	    if (HTML)
		printf("\n<DT>");
	    else if (LATEX) {
		if (name[0] == ' ') {
		    name++;
		    printf("\\item[\\BX{");
		} else
		    printf("\\item[\\JX{");
	    }
	    if (HTML && strcmp(name, "<=") == 0)
		printf("&lt;=");
	    else
		printf("%s", name);
	    if (LATEX)
		printf("}]  \\verb#");
	    if (HTML)
		printf("<CODE> : </CODE>");
	    /* the above line does not produce the spaces around ":" */
	    else
		printf("\t:  ");
	    printf("%s", optable[i].messg1);
	    if (HTML)
		printf("\n<DD>");
	    else if (LATEX)
		printf("# \\\\ \n {\\small\\verb#");
	    else
		printf("\n");
	    printf("%s", optable[i].messg2);
	    if (LATEX)
		printf("#}");
	    printf("\n\n");
	}
    }
    if (HTML)
	printf("\n</DL>\n</HTML>\n");
}

/**
manual  :  ->
Writes this manual of all Joy primitives to output file.
*/
PRIVATE void do_manual(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    make_manual(0);
}
