/*
    module  : joy.h
    version : 1.9
    date    : 03/12/17
*/
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

typedef struct optable_t {
    char *name, *messg1, *messg2;
} optable_t;

#ifndef PARSER
#include "gc.h"
#include "parse.h"
#endif

/* initsym.c */
extern FILE *outfp;
extern char **g_argv;
extern int g_argc, error;
extern unsigned compiling, optimizing, identifier;
extern unsigned autoput, undeferror, echoflag, tracegc;

/* lexer.l */
extern FILE *yyin, *yyout;

/* compile.c */
char *usrname(char *str);
void printstack(FILE *fp);
void initialise(void);
void finalise(void);

/* initmem.c */
void initmem(void);
void checkmem(void);

/* initsym.c */
void initsym(int argc, char **argv);
void execerror(char *message, const char *op);

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

/* listing.c */
void NewScope(void);
void OldScope(void);
unsigned Listed(void *ptr, int *found);
void DeList(void);

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
