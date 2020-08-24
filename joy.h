/*
    module  : joy.h
    version : 1.26
    date    : 03/28/20
*/
#ifndef JOY_H
#define JOY_H

#include <stdio.h>

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
#define PRINT_SET	"%lu"

typedef long		long_t;
typedef unsigned long	ulong_t;
typedef float		real_t;
#endif

#ifdef BIT_64
#define SETSIZE_	64
#define MAXINT_		9223372036854775807LL
#define PRINT_NUM	"%lld"
#define PRINT_SET	"%llu"

typedef long long	long_t;
typedef unsigned long long	ulong_t;
typedef double		real_t;
#endif

#include "joygc.h"
#ifndef PARSER
#include "parse.h"
#endif

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

/* compile.c */
void printstack(FILE *fp);
void initialise(void);
void finalise(void);

/* main.c */
void execerror(char *message, const char *op);

/* initsym.c */
void initsym(int argc, char **argv);

/* outfile.c */
void initout(void);
FILE *nextfile(void);
void closefile(FILE *fp);
void printout(FILE *fp);
void closeout(void);

/* parse.y */
int yyparse(void);

/* yylex.c */
void inilinebuffer(FILE *fp, char *str);
int yylex(void);
int getechoflag(void);
void setechoflag(int flag);
int yyerror(char *str);
void new_buffer(void);
int old_buffer(void);

/* utils.c */
void readfactor(int sym);
void readterm(int sym);

/* joy.c */
int ChrVal(char *str);
char *StrVal(char *str);
char *DelSpace(char *str);

/* scan.c */
void redirect(FILE *fp);
void include(char *filnam);
int yywrap(void);
#endif
