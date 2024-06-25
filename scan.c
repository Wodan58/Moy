/*
    module  : scan.c
    version : 1.22
    date    : 06/22/24
*/
#include "globals.h"

extern FILE *yyin;
extern char line[];
extern int yylineno;

static int ilevel;

static struct {
    FILE *fp;
    int line;
    char name[FILENAMEMAX + 1];
} infile[INPSTACKMAX];

/*
 * inilinebuffer - initialise the stack of input files. The filename parameter
 *		   is used in error messages.
 */
void inilinebuffer(pEnv env)
{
    infile[0].fp = yyin;
    infile[0].line = 1;			/* start with line 1 */
    strncpy(infile[0].name, env->filename, FILENAMEMAX);
}

/*
 * redirect - read from another file descriptor.
 */
static void redirect(FILE *fp, char *str)
{
    infile[ilevel].line = yylineno;	/* save last line number and line */
    if (ilevel + 1 == INPSTACKMAX)	/* increase the include level */
	execerror("fewer include files", "include");
    infile[++ilevel].fp = yyin = fp; 	/* update yyin, used by yylex */
    infile[ilevel].line = 1;		/* start with line 1 */
    strncpy(infile[ilevel].name, str, FILENAMEMAX);
    new_buffer();			/* new file, new buffer */
}

/*
 * include - insert the contents of a file in the input.
 *
 * Files are read in the current directory or if that fails from the previous
 * location. Generating an error is left to the call site.
 *
 * Return code is 1 if the file could not be opened.
 */
int include(pEnv env, char *name)
{
    FILE *fp;
    char *path = 0, *str = name;

    /*
     * A file is first tried in the current directory.
     */
    if ((fp = fopen(name, "r")) != 0)
	goto normal;
    /*
     * usrlib.joy is tried in the home directory and then in the directory
     * where the joy binary is located.
     */
    if (!strcmp(name, "usrlib.joy")) {			/* check usrlib.joy */
	if ((path = getenv("HOME")) != 0) {		/* unix/cygwin */
	    str = GC_malloc_atomic(strlen(path) + strlen(name) + 2);
	    sprintf(str, "%s/%s", path, name);
	    if ((fp = fopen(str, "r")) != 0)
		goto normal;
	}
	if ((path = getenv("USERPROFILE")) != 0) {	/* windows */
	    str = GC_malloc_atomic(strlen(path) + strlen(name) + 2);
	    sprintf(str, "%s/%s", path, name);
	    if ((fp = fopen(str, "r")) != 0)
		goto normal;
	}
    }
    /*
     * If that fails, the pathname is prepended and the file is tried again.
     */
    path = env->pathname;				/* joy binary */
    if (strcmp(path, ".")) {
	str = GC_malloc_atomic(strlen(path) + strlen(name) + 2);
	sprintf(str, "%s/%s", path, name);
	if ((fp = fopen(str, "r")) == 0)
	    return 1;
    }
normal:
    /*
     * If there is a new pathname, replace the old one.
     */
    if (strrchr(str, '/')) {
	env->pathname = GC_strdup(str);
	path = strrchr(env->pathname, '/');
	*path = 0;
    }
    redirect(fp, name);
    return 0;
}

/*
 * my_yywrap - continue reading after EOF.
 */
int my_yywrap(pEnv env)
{
    if (!ilevel)			/* at end of first file, end program */
	return 1;			/* terminate */
    fclose(infile[ilevel].fp);		/* close file */
    infile[ilevel].fp = 0;		/* invalidate file pointer */
    yyin = infile[--ilevel].fp;		/* proceed with previous file */
    old_buffer(infile[ilevel].line);	/* and previous input buffer */
    if (env->finclude_busy)
	longjmp(env->finclude, 1);	/* back to finclude */
    return 0;				/* continue with old buffer */
}

/*
 * my_error - error processing during parsing; location info as parameter.
 */
void my_error(char *str, YYLTYPE *bloc)
{
    int leng = bloc->last_column - 1;

    fflush(stdout);
    leng += fprintf(stderr, "%s:%d:", infile[ilevel].name, yylineno);
    fprintf(stderr, "%s\n%*s^\n%*s%s\n", line, leng, "", leng, "", str);
    line[0] = 0;	/* invalidate line */
    abortexecution_(ABORT_RETRY);
}	/* LCOV_EXCL_LINE */

/*
 * yyerror - error processing during source file read; location info global.
 */
void yyerror(pEnv env, char *str)
{
    YYLTYPE bloc;

    bloc.last_column = yylloc.last_column;
    my_error(str, &bloc);
}	/* LCOV_EXCL_LINE */
