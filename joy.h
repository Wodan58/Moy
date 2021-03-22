/*
    module  : joy.h
    version : 1.27
    date    : 03/15/21
*/
#ifndef JOY_H
#define JOY_H

#include <stdio.h>

#ifdef _MSC_VER
#define __func__	__FUNCTION__
#pragma warning(disable : 4244 4305 4996)
#include <io.h>
#else
#include <unistd.h>
#endif

#define BIT_64

#ifdef BIT_32
#define SETSIZE_	32
#define MAXINT_		2147483647

typedef int		long_t;
typedef unsigned	ulong_t;
typedef float		real_t;
#endif

#ifdef BIT_64
#define SETSIZE_	64
#define MAXINT_		9223372036854775807

typedef long		long_t;
typedef unsigned long	ulong_t;
typedef double		real_t;
#endif

typedef struct Env *pEnv;

typedef void (*proc_t)(pEnv env);

#include "gc.h"
#ifndef PARSER
#include "parse.h"

extern YYSTYPE bucket;
#endif

/* main.c, parse.y */
extern pEnv environment;

typedef struct optable_t {
    char *name, *messg1, *messg2;
} optable_t;

/* optable.c */
extern optable_t optable[];

/* initsym.c */
extern FILE *outfp, *declfp;
extern char **g_argv;
extern int g_argc, compiling, debugging, definition, interpreter, nologo;
extern int autoput, tracegc, undeferror;

/* lexer.l, scan.c, yylex.c */
int getechoflag(void);
void setechoflag(int flag);
int yyerror(char *str);
int yylex(void);

/* compile.c */
void initialise(void);

/* main.c */
void execerror(char *message, const char *op);

/* joy.c */
int ChrVal(char *str);
char *StrVal(char *str);
char *DelSpace(char *str);

/* lexer.l */
int yylook(void);
int yyback(int *p, int m);
void new_buffer(void);
int old_buffer(void);

/* outfile.c */
void initout(void);
FILE *nextfile(void);
void closefile(FILE *fp);
void printout(FILE *fp);
void closeout(void);

/* parse.y */
int yyparse(void);

/* scan.c, yylex.c */
void inilinebuffer(FILE *fp, char *str);
void redirect(FILE *fp);
void include(char *filnam);
int yywrap(void);

#define NEWNODE(o, u, r) (bucket.ptr = newnode((o), (u), (r)), bucket.ptr)
#define USR_NEWNODE(u, r) (bucket.num = (u), NEWNODE(USR_, bucket, (r)))
#define ANON_FUNCT_NEWNODE(u, r)                                               \
        (bucket.ptr = (u), NEWNODE(ANON_FUNCT_, bucket, (r)))
#define BOOLEAN_NEWNODE(u, r) (bucket.num = (u), NEWNODE(BOOLEAN_, bucket, (r)))
#define CHAR_NEWNODE(u, r) (bucket.num = (u), NEWNODE(CHAR_, bucket, (r)))
#define INTEGER_NEWNODE(u, r) (bucket.num = (u), NEWNODE(INTEGER_, bucket, (r)))
#define SET_NEWNODE(u, r) (bucket.num = (u), NEWNODE(SET_, bucket, (r)))
#define STRING_NEWNODE(u, r) (bucket.ptr = (u), NEWNODE(STRING_, bucket, (r)))
#define LIST_NEWNODE(u, r) (bucket.ptr = (u), NEWNODE(LIST_, bucket, (r)))
#define FLOAT_NEWNODE(u, r) dblnode((u), (r))
#define FILE_NEWNODE(u, r) (bucket.ptr = (u), NEWNODE(FILE_, bucket, (r)))
#define SYM_NEWNODE(u, r) (bucket.ptr = (u), NEWNODE(SYMBOL_, bucket, (r)))
#endif
