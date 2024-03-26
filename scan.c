/*
    module  : scan.c
    version : 1.18
    date    : 03/21/24
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
	execerror(str, "fewer include files", "include");
    infile[++ilevel].fp = yyin = fp; 	/* update yyin, used by yylex */
    infile[ilevel].line = 1;		/* start with line 1 */
    strncpy(infile[ilevel].name, str, FILENAMEMAX);
    new_buffer();			/* new file, new buffer */
}

/*
 * include - insert the contents of a file in the input.
 *
 * Files are read in the current directory or if that fails from the previous
 * location. If that also fails an error is generated.
 */
void include(pEnv env, char *name)
{
    /*
     * mustinclude - determine whether an attempt must be made to include
     * usrlib.joy
     */
    FILE *fp;
    char *path = 0, *str = name;

    /*
     * usrlib.joy is tried first in the current directory, then in the home
     * directory and then in the directory where the joy binary is located.
     *
     * If all of that fails, no harm done.
     */
    if (!strcmp(name, "usrlib.joy")) {			/* check usrlib.joy */
	if ((fp = fopen(name, "r")) != 0)
	    goto normal;
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
	path = env->pathname;				/* joy binary */
	if (strcmp(path, ".")) {
	    str = GC_malloc_atomic(strlen(path) + strlen(name) + 2);
	    sprintf(str, "%s/%s", path, name);
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
	    path = strrchr(env->pathname, '/');
	    *path = 0;
	}
	redirect(fp, name);
	return;
    }
    /*
     * A file other than usrlib.joy is tried first in the current directory.
     */
    if ((fp = fopen(name, "r")) != 0)
	goto normal;
    /*
     * If that fails, the pathname is prepended and the file is tried again.
     */
    path = env->pathname;
    if (strcmp(path, ".")) {
	str = GC_malloc_atomic(strlen(path) + strlen(name) + 2);
	sprintf(str, "%s/%s", path, name);
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
 * yywrap - continue reading after EOF.
 */
int yywrap(void)
{
    if (!ilevel)			/* at end of first file, end program */
	return 1;			/* terminate */
    fclose(infile[ilevel].fp);		/* close file */
    infile[ilevel].fp = 0;		/* invalidate file pointer */
    yyin = infile[--ilevel].fp;		/* proceed with previous file */
    old_buffer(infile[ilevel].line);	/* and previous input buffer */
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
}

/*
 * yyerror - error processing during source file read; location info global.
 */
void yyerror(pEnv env, char *str)
{
    YYLTYPE bloc;

    bloc.last_column = yylloc.last_column;
    my_error(str, &bloc);
}
