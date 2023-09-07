/*
    module  : scan.c
    version : 1.9
    date    : 09/07/23
*/
#include "globals.h"

extern FILE *yyin;
extern char line[];
extern int yylineno;

static int ilevel, fget_eof;

static struct {
    FILE *fp;
    int line;
    char *name;
} infile[INPSTACKMAX];

/*
    inilinebuffer - initialise the stack of input files. The filename parameter
		    could be used in error messages.
*/
PUBLIC void inilinebuffer(char *str)
{
    infile[0].fp = yyin;
    infile[0].line = 1;
    infile[0].name = str;
}

/*
    redirect - read from another file descriptor. Some special processing in
	       the case of reading with fget.
*/
PUBLIC int redirect(char *name, FILE *fp)
{
    if (fget_eof) {			/* stop reading from this file */
	fget_eof = 0;
	return 0;			/* abort fget functionality */
    }
    if (!strcmp(infile[ilevel].name, name))
	return 1;			/* already reading from this file */
    infile[ilevel].line = yylineno;	/* save last line number and line */
    if (ilevel + 1 == INPSTACKMAX)	/* increase the include level */
	execerror("fewer include files", "include");
    infile[++ilevel].fp = yyin = fp; 	/* update yyin, used by yylex */
    infile[ilevel].line = 1;		/* start with line 1 */
    infile[ilevel].name = name;
    new_buffer();			/* really new buffer */
    return 1;				/* ok, switched to new file, buffer */
}

/*
    include - insert the contents of a file in the input.

	      Files are read in the current directory or if that fails
	      from the same directory as where the executable is stored.
	      If that path also fails an error is generated unless error
	      is set to 0.
*/
PUBLIC int include(pEnv env, char *name, int error)
{
    FILE *fp;
    char *ptr, *str;

/*
    First try to open name in the current working directory.
*/
    if ((fp = fopen(name, "r")) != 0) {
/*
    Replace the pathname of argv[0] with the pathname of name.
*/
	if (strchr(name, '/')) {
	    env->pathname = GC_strdup(name);
	    ptr = strrchr(env->pathname, '/');
	    *ptr = 0;
	}
/*
    Prepend pathname to the filename and try again.
*/
    } else if (strcmp(env->pathname, ".")) {
	str = GC_malloc_atomic(strlen(env->pathname) + strlen(name) + 2);
	sprintf(str, "%s/%s", env->pathname, name);
	if ((fp = fopen(str, "r")) != 0) {
/*
    If this succeeds, establish a new pathname.
*/
	    env->pathname = GC_strdup(str);
	    ptr = strrchr(env->pathname, '/');
	    *ptr = 0;
	}
    }
    if (fp && redirect(name, fp))
	return 0; /* ok */
    if (error)
	execerror("valid file name", "include");
    return 1; /* nok */
}

/*
    yywrap - continue reading after EOF.
*/
int yywrap(void)
{
    if (!ilevel)			/* at end of first file, end program */
	return 1;			/* terminate */
    if (!strcmp(infile[ilevel].name, "fget"))
	fget_eof = 1;
    fclose(infile[ilevel].fp);		/* close file */
    infile[ilevel].fp = 0;		/* invalidate file pointer */
    yyin = infile[--ilevel].fp;		/* proceed with previous file */
    old_buffer(infile[ilevel].line);	/* and previous input buffer */
    return 0;				/* continue with old buffer */
}

/*
    my_error - error processing during parsing; location info as parameter.
*/
void my_error(char *str, YYLTYPE *bloc)
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
int yyerror(pEnv env, char *str)
{
    YYLTYPE bloc;

    bloc.last_column = yylloc.last_column;
    my_error(str, &bloc);
    env->nothing++;
    return 0;
}
