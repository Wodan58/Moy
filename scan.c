/*
    module  : scan.c
    version : 1.5
    date    : 08/23/23
*/
#include "globals.h"

extern FILE *yyin;
extern char line[];
extern int yylineno;

static int ilevel;

static struct {
    FILE *fp;
    char *name;
    int linenum;
} infile[INPSTACKMAX];

/*
    inilinebuffer - initialise the stack of input files. The filename parameter
		    could be used in error messages.
*/
PUBLIC void inilinebuffer(char *str)
{
    infile[0].fp = yyin;
    infile[0].name = str ? str : "stdin";
}

PRIVATE void redirect(char *filnam, FILE *fp)
{
    infile[ilevel].linenum = yylineno; /* save last line number */
    if (ilevel + 1 == INPSTACKMAX)
	execerror("fewer include files", "include");
    infile[++ilevel].fp = yyin = fp;
    infile[ilevel].name = filnam;
    infile[ilevel].linenum = 1; /* start with line 1 */
    new_buffer();
}

/*
    include - insert the contents of a file in the input.

	      Files are read in the current directory or if that fails
	      from the same directory as where the executable is stored.
	      If that path also fails an error is generated unless error
	      is set to 0.
*/
PUBLIC int include(pEnv env, char *filnam, int error)
{
    FILE *fp;
    char *ptr, *str;

/*
    First try to open filnam in the current working directory.
*/
    if ((fp = fopen(filnam, "r")) != 0) {
/*
    Replace the pathname of argv[0] with the pathname of filnam.
*/
	if (strchr(filnam, '/')) {
	    env->pathname = GC_strdup(filnam);
	    ptr = strrchr(env->pathname, '/');
	    *ptr = 0;
	}
    }
/*
    Prepend pathname to the filename and try again.
*/
    else if (strcmp(env->pathname, ".")) {
	str = GC_malloc_atomic(strlen(env->pathname) + strlen(filnam) + 2);
	sprintf(str, "%s/%s", env->pathname, filnam);
	if ((fp = fopen(str, "r")) != 0) {
/*
    If this succeeds, establish a new pathname.
*/
	    env->pathname = GC_strdup(str);
	    ptr = strrchr(env->pathname, '/');
	    *ptr = 0;
	}
    }
    if (fp) {
	redirect(filnam, fp);
	return 0; /* ok */
    }
    if (error)
	execerror("valid file name", "include");
    return 1; /* nok */
}

/*
    yywrap - continue reading after EOF.
*/
int yywrap(void)
{
    if (!ilevel)
	return 1;
    yyin = infile[--ilevel].fp;
    old_buffer(infile[ilevel].linenum);
    return 0;
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
    abortexecution_();
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
