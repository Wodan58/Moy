/*
    module  : scan.c
    version : 1.11
    date    : 06/23/22
*/
#include "globals.h"

extern FILE *yyin;
extern char line[], *yytext;
extern int yylineno, yyleng;

static int ilevel;

static struct {
    FILE *fp;
#if 0
    char name[ALEN];
#endif
    int linenum;
} infile[INPSTACKMAX];

void inilinebuffer(void)
{
    infile[0].fp = yyin = stdin;
#if 0
    strncpy(infile[0].name, name, ALEN);
    infile[0].name[ALEN - 1] = 0;
#endif
    infile[0].linenum = 0;
}

static void redirect(pEnv env, FILE *fp)
{
    infile[ilevel].linenum = yylineno;
    if (ilevel + 1 == INPSTACKMAX)
        execerror(env, "fewer include files", "redirect");
    infile[++ilevel].fp = yyin = fp;
#if 0
    strncpy(infile[ilevel].name, name, ALEN);
    infile[ilevel].name[ALEN - 1] = 0;
#endif
    infile[ilevel].linenum = yylineno = 0;
    new_buffer(env);
}

/*
    include - insert the contents of a file in the input. If the file cannot be
              found in the current directory, it is searched in the same
              directory as the executable.
*/
void include(pEnv env, char *name, int error)
{
    FILE *fp;
    int leng;
    char *path, *str;

    if ((fp = fopen(name, "r")) != 0)
        ;
    else if ((path = strrchr(g_argv[0], '/')) != 0) {
        leng = path - g_argv[0];
        str = GC_malloc_atomic(leng + strlen(name) + 2);
        sprintf(str, "%.*s/%s", leng, g_argv[0], name);
        fp = fopen(str, "r");
    }
    if (fp)
        redirect(env, fp);
    else if (error)
        execerror(env, "valid file name", "include");
}

int yywrap(void)
{
    if (yyin != stdin)
        fclose(yyin);
    if (!ilevel)
        return 1;
    yyin = infile[--ilevel].fp;
    yylineno = infile[ilevel].linenum;
    old_buffer();
    return 0;
}

int yyerror(pEnv env, char *str)
{
    int i, j;

    if (line[0]) {
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
    abortexecution();
    return 0;
}
