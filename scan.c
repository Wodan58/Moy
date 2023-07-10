/*
    module  : scan.c
    version : 1.1
    date    : 07/10/23
*/
#include "globals.h"

extern FILE *yyin;
extern char line[], *yytext;
extern int yylineno, yyleng;

static int ilevel;

static struct {
    FILE *fp;
#ifdef REMEMBER_FILENAME
    char *name;
#endif
    int linenum;
} infile[INPSTACKMAX];

/*
    inilinebuffer - initialise the stack of input files. The filename parameter
                    could be used in error messages.
*/
#ifdef REMEMBER_FILENAME
PUBLIC void inilinebuffer(char *str)
#else
PUBLIC void inilinebuffer(void)
#endif
{
    infile[0].fp = yyin;
#ifdef REMEMBER_FILENAME
    infile[0].name = str ? str : "stdin";
#endif
}

#ifdef REMEMBER_FILENAME
PRIVATE void redirect(char *filnam, FILE *fp)
#else
PRIVATE void redirect(FILE *fp)
#endif
{
    infile[ilevel].linenum = yylineno;
    if (ilevel + 1 == INPSTACKMAX)
        execerror("fewer include files", "include");
    infile[++ilevel].fp = yyin = fp;
#ifdef REMEMBER_FILENAME
    infile[ilevel].name = filnam;
#endif
    infile[ilevel].linenum = yylineno = 0;
    new_buffer();
}

/*
    include - insert the contents of a file in the input.

              Files are read in the current directory or if that fails
              from the same directory as where the executable is stored.
              If that path also fails an error is generated unless error
              is set to 0.
*/
PUBLIC void include(pEnv env, char *filnam, int error)
{
    FILE *fp;
    char *ptr;
#ifdef SEARCH_EXEC_DIRECTORY
    char *str;
#endif

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
#ifdef SEARCH_EXEC_DIRECTORY
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
#endif
    if (fp)
#ifdef REMEMBER_FILENAME
        redirect(filnam, fp);
#else
        redirect(fp);
#endif
    else if (error)
        execerror("valid file name", "include");
}

/*
    yywrap - continue reading after EOF.
*/
int yywrap(void)
{
    if (!ilevel)
        return 1;
    yyin = infile[--ilevel].fp;
    yylineno = infile[ilevel].linenum;
    old_buffer();
    return 0;
}

/*
    yyerror - error processing during source file reads.
*/
int yyerror(pEnv env, char *str)
{
    int i, j;

    if (line[0]) {
        fflush(stdout);
        fprintf(stderr, "%s\n", line);
        for (i = strlen(line) - yyleng; i >= 0; i--)
            if (!strncmp(&line[i], yytext, yyleng)) {
                for (j = 0; j < i; j++)
                    fputc(' ', stderr);
                break;
            }
        fprintf(stderr, "^\n\t%s\n", str);
        line[0] = 0;
    }
    vec_resize(env->stck, 0);
    abortexecution_();
    return 0;
}
