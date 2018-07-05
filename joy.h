/*
    module  : joy.h
    version : 1.19
    date    : 07/05/18
*/
#ifdef _MSC_VER
#include <io.h>
#else
#include <unistd.h>
#endif

#define BIT_32

#ifdef BIT_32
#define SETSIZE_	32
#define MAXINT_		2147483647
#define PRINT_NUM	"%ld"

typedef long		long_t;
typedef unsigned long	ulong_t;
typedef float		real_t;
#endif

#ifdef BIT_64
#define SETSIZE_	64
#define MAXINT_		9223372036854775807LL
#define PRINT_NUM	"%lld"

typedef long long	long_t;
typedef unsigned long long	ulong_t;
typedef double		real_t;
#endif

#ifndef PARSER
#include "joygc.h"
#include "parse.h"
#endif

typedef struct optable_t {
    char *name, *messg1, *messg2;
} optable_t;

/* optable.c */
extern optable_t optable[];

/* initsym.c */
extern FILE *outfp, *declfp;
extern char **g_argv, *mainfunc;
extern int g_argc, debugging, compiling, definition;
extern int autoput, tracegc, undeferror;

/* lexer.l */
extern int yylineno;
extern FILE *yyin, *yyout;

int getechoflag(void);
void setechoflag(int flag);

/* compile.c */
void printstack(FILE *fp);
void initialise(void);
void finalise(void);

/* error.c */
void execerror(char *message, const char *op);

/* initmem.c */
void initmem(void);

/* initsym.c */
void initsym(int argc, char **argv);

/* joy.c */
int ChrVal(char *str);
char *StrVal(char *str);
char *DelSpace(char *str);

/* lexer.l */
int yylook(void);
int yyback(int *p, int m);
int yyerror(char *str);
int yylex(void);
void new_buffer(void);
int old_buffer(void);

/* outfile.c */
void initout(void);
FILE *nextfile(void);
void closefile(FILE *fp);
void printout(void);
void closeout(void);

/* parse.y */
int yyparse(void);

/* scan.c */
void redirect(FILE *fp);
void include(char *filnam);
int yywrap(void);

/* utils.c */
void readfactor(int sym);
void readterm(int sym);
