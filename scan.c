/*
    module  : scan.c
    version : 1.16
    date    : 02/13/24
*/
#include "globals.h"

extern FILE *yyin;
extern char line[];
extern int yylineno;

static int ilevel;
static char my_line[INPLINEMAX + 1];
static unsigned char my_echoflag;

static struct {
    FILE *fp;
    int line;
    char *name;
} infile[INPSTACKMAX];

/*
 * Possibly echo a line.
 */
PRIVATE void echoline(void)
{
    if (!my_echoflag || !my_line[0])
	return;
    if (my_echoflag > 2)
	printf("%4d", 1);
    if (my_echoflag > 1)
	putchar('\t');
    printf("%s", my_line);
    my_line[0] = 0;
}

/*
    inilinebuffer - initialise the stack of input files. The filename parameter
		    is used in error messages. Also read the first line.
*/
PUBLIC void inilinebuffer(pEnv env, int joy)
{
    infile[0].fp = yyin;
    infile[0].line = 1;			/* start with line 1 */
    infile[0].name = env->filename;
    if (!joy)				/* test whether compiler active */
	return;
    if (fgets(my_line, INPLINEMAX, yyin))	/* read first line */
	rewind(yyin);
    my_echoflag = env->echoflag;
}

/*
    redirect - read from another file descriptor. Some special processing in
	       the case of reading with fget.
*/
PRIVATE void redirect(char *str, FILE *fp)
{
    if (infile[ilevel].fp == fp)
	return;				/* already reading from this file */
    infile[ilevel].line = yylineno;	/* save last line number and line */
    if (ilevel + 1 == INPSTACKMAX)	/* increase the include level */
	execerror(str, "fewer include files", "include");
    infile[++ilevel].fp = yyin = fp; 	/* update yyin, used by yylex */
    infile[ilevel].line = 1;		/* start with line 1 */
    infile[ilevel].name = str;
    new_buffer();			/* new file, new buffer */
}

/*
    include - insert the contents of a file in the input.

    Files are read in the current directory or if that fails from the
    previous location. If that also fails an error is generated.
*/
PUBLIC void include(pEnv env, char *name)
{
    /*
     * mustinclude - determine whether an attempt must be made to include
     * usrlib.joy
     */
    FILE *fp;
    char *ptr, *str;

    /*
     * usrlib.joy is tried first in the current directory, then in the home
     * directory and then in the directory where the joy binary is located.
     *
     * If all of that fails, no harm done.
     */
    str = name;						/* name copied to str */
    if (!strcmp(name, "usrlib.joy")) {			/* check usrlib.joy */
	if ((fp = fopen(str, "r")) != 0)
	    goto normal;
	if ((ptr = getenv("USERPROFILE")) != 0) {	/* windows */
	    str = GC_malloc_atomic(strlen(ptr) + strlen(name) + 2);
	    sprintf(str, "%s/%s", ptr, name);
	    if ((fp = fopen(str, "r")) != 0)
		goto normal;
	}
	if ((ptr = getenv("HOME")) != 0) {
	    str = GC_malloc_atomic(strlen(ptr) + strlen(name) + 2);
	    sprintf(str, "%s/%s", ptr, name);
	    if ((fp = fopen(str, "r")) != 0)
		goto normal;
	}
	if (strcmp(env->pathname, ".")) {
	    str = GC_malloc_atomic(strlen(env->pathname) + strlen(name) + 2);
	    sprintf(str, "%s/%s", env->pathname, name);
	    if ((fp = fopen(str, "r")) != 0)
		goto normal;
	}
	/*
	 * Failure to open usrlib.joy need not be reported.
	 */
	return;
normal:
	/*
	 * If there is a new pathname, replace the old one.
	 */
	if (strrchr(str, '/')) {
	    env->pathname = GC_strdup(str);
	    ptr = strrchr(env->pathname, '/');
	    *ptr = 0;
	}
	redirect(name, fp);
	my_echoflag = env->echoflag;
	return;
    }
    /*
     * A file other that usrlib.joy is first tried in the current directory.
     */
    if ((fp = fopen(name, "r")) != 0)
	goto normal;
    /*
     * If that fails, the pathname is prepended and the file is tried again.
     */
    if (strcmp(env->pathname, ".")) {
	str = GC_malloc_atomic(strlen(env->pathname) + strlen(name) + 2);
	sprintf(str, "%s/%s", env->pathname, name);
	if ((fp = fopen(str, "r")) != 0)
	    goto normal;
    }
    /*
     * If that also fails, no other path can be tried and an error is
     * generated.
     */
    execerror(name, "valid file name", "include");
}

/*
    yywrap - continue reading after EOF.
*/
PUBLIC int yywrap(void)
{
    if (!ilevel)			/* at end of first file, end program */
	return 1;			/* terminate */
    fclose(infile[ilevel].fp);		/* close file */
    infile[ilevel].fp = 0;		/* invalidate file pointer */
    yyin = infile[--ilevel].fp;		/* proceed with previous file */
    old_buffer(infile[ilevel].line);	/* and previous input buffer */
    if (!ilevel	&& yylineno == 1)	/* if back to first input file */
	echoline();
    return 0;				/* continue with old buffer */
}

/*
    my_error - error processing during parsing; location info as parameter.
*/
PUBLIC void my_error(char *str, YYLTYPE *bloc)
{
    int leng = bloc->last_column - 1;

    fflush(stdout);
    leng += fprintf(stderr, "%s:%d:", infile[ilevel].name, yylineno);
    fprintf(stderr, "%s\n%*s^\n%*s%s\n", line, leng, "", leng, "", str);
    line[0] = 0; /* invalidate line */
    abortexecution_(PARS_ERR);
}

/*
    yyerror - error processing during source file read; location info global.
*/
PUBLIC int yyerror(pEnv env, char *str)
{
    YYLTYPE bloc;

    bloc.last_column = yylloc.last_column;
    my_error(str, &bloc);
    return 0;
}
