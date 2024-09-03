/*
    module  : scan.c
    version : 1.25
    date    : 08/30/24
*/
#include "globals.h"

extern FILE *yyin;
extern char line[];
extern int yylineno;

static int ilevel = -1;

static struct {
    FILE *fp;
    int line;
    char name[FILENAMEMAX + 1];
} infile[INPSTACKMAX];

/*
 * redirect - register another file descriptor to read from.
 */
static void redirect(pEnv env, char *str, FILE *fp)
{
    int i;
    char *new_path, *old_path;

    /*
     * If a filename is given with a pathname, then that pathname will be used
     * for additional attempts.
     */
    if (strrchr(str, '/')) {
	new_path = GC_strdup(str);
	str = strrchr(new_path, '/');
	*str++ = 0;
	for (i = vec_size(env->pathnames) - 1; i >= 0; i--) {
	    old_path = vec_at(env->pathnames, i);
	    if (!strcmp(new_path, old_path))
		break;
	}
	if (i < 0)
	    vec_push(env->pathnames, new_path);
    }
    if (ilevel >= 0)
	infile[ilevel].line = yylineno;	/* save last line number */
    if (ilevel + 1 == INPSTACKMAX)	/* increase include level */
	execerror("fewer include files", "include");
    infile[++ilevel].fp = yyin = fp;	/* use new file pointer */
    infile[ilevel].line = 1;		/* start with line 1 */
    strncpy(infile[ilevel].name, str, FILENAMEMAX);
    new_buffer();			/* new file, new buffer */
}

/*
 * inilinebuffer - initialise the stack of input files. The filename parameter
 *		   is used in error messages.
 */
void inilinebuffer(pEnv env)
{
    redirect(env, "stdin", stdin);
}

/*
 * include - insert the contents of a file in the input.
 *
 * Files are read in the current directory or if that fails from a previous
 * location. Generating an error is left to the call site.
 *
 * Return code is 1 if the file could not be opened for reading.
 */
int include(pEnv env, char *name)
{
    int i;
    FILE *fp;
    char *path, *str = name;			/* str = path/name */

    /*
     * The home directory is added to the list of directories to be searched.
     */
    if (!env->homedir) {			/* should be present */
	env->homedir = getenv("HOME");		/* unix/cygwin */
#ifdef WINDOWS
	if (!env->homedir)
	    env->homedir = getenv("HOMEPATH");	/* windows */
#endif
	if (env->homedir)
	    vec_push(env->pathnames, env->homedir);
    }
    /*
     * The current directory is tried first.
     * Then all saved directories are tried until there is one that succeeds.
     */
    for (i = vec_size(env->pathnames); i >= 0; i--) {
	if (i != vec_size(env->pathnames)) {
	    path = vec_at(env->pathnames, i);
	    str = GC_malloc_atomic(strlen(path) + strlen(name) + 2);
	    sprintf(str, "%s/%s", path, name);
	}
	if ((fp = fopen(str, "r")) != 0) {	/* try to read */
	    redirect(env, str, fp);		/* stop trying */
	    return 0;
	}
    }
    return 1;		/* file cannot be opened for reading */
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
