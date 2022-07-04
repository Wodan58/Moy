/*
    module  : globals.h
    version : 1.31
    date    : 06/19/22
*/
#ifndef GLOBALS_H
#define GLOBALS_H

#ifndef RUNTIME
#define COMPILING
#endif

#ifndef COSMO
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <inttypes.h>
#include <setjmp.h>
#include <assert.h>
#include <errno.h>
#include <math.h>
#include <time.h>

#ifdef _MSC_VER
#define __func__	__FUNCTION__
#pragma warning(disable : 4244 4305 4996)
#include <io.h>
#else
#include <unistd.h>
#endif
#endif

/*
    The hash tables in compile.c and symbol.c contain pointers allocated with
    GC_ functions.
*/
#define kcalloc(N, Z)	GC_malloc((N) * (Z))
#define kmalloc(Z)	GC_malloc(Z)
#define krealloc(P, Z)	GC_realloc(P, Z)
#define kfree(P)

#include "decl.h"
#ifdef COSMO
#include "gc.h"
#else
#include <gc.h>
#endif
#include "kvec.h"
#include "khash.h"

#define BIT_64

#ifdef BIT_32
#define SETSIZE_	32
#define MAXINT_		2147483647
#endif

#ifdef BIT_64
#define SETSIZE_	64
#define MAXINT_		9223372036854775807
#endif

typedef struct Env *pEnv;
typedef void (*proc_t)(pEnv);

#include "parse.h"
#include "environ.h"
#include "symbol.h"
#include "node.h"
#include "builtin.h"

typedef struct optable_t {
    char *name, *messg1, *messg2;
} optable_t;

/* optable.c */
extern optable_t optable[];

/* initsym.c */
extern clock_t startclock;
extern FILE *outfp, *declfp;
extern char **g_argv;
extern int g_argc, library, compiling, debugging, interpreter;
extern int autoput, tracegc, undeferror;

/* quit.c, lexer.l, scan.c, yylex.c */
void my_atexit(void (*proc)(pEnv));
int getnextchar(void);
int getechoflag(void);
void setechoflag(int flag);
void new_buffer(pEnv env);
int old_buffer(void);
void inilinebuffer(void);
void include(pEnv env, char *name, int error);
int yywrap(void);
int yyerror(pEnv env, char *str);
int yylex(pEnv env);

/* main.c */
void abortexecution(void);

/* joy.c */
int ChrVal(char *str);
char *StrVal(char *str);
char *DelSpace(char *str);

/* outfile.c */
void initout(void);
FILE *nextfile(void);
void closefile(FILE *fp);
void printout(FILE *fp);
void closeout(void);

#define NEWNODE(o, u, r)						       \
	(env->bucket.ptr = newnode((o), (u), (r)), env->bucket.ptr)
#define USR_NEWNODE(u, r)						       \
	(env->bucket.num = (u), NEWNODE(USR_, env->bucket, (r)))
#define ANON_FUNCT_NEWNODE(u, r)					       \
	(env->bucket.ptr = (u), NEWNODE(ANON_FUNCT_, env->bucket, (r)))
#define BOOLEAN_NEWNODE(u, r)						       \
	(env->bucket.num = (u), NEWNODE(BOOLEAN_, env->bucket, (r)))
#define CHAR_NEWNODE(u, r)						       \
	(env->bucket.num = (u), NEWNODE(CHAR_, env->bucket, (r)))
#define INTEGER_NEWNODE(u, r)						       \
	(env->bucket.num = (u), NEWNODE(INTEGER_, env->bucket, (r)))
#define SET_NEWNODE(u, r)						       \
	(env->bucket.num = (u), NEWNODE(SET_, env->bucket, (r)))
#define STRING_NEWNODE(u, r)						       \
	(env->bucket.ptr = (u), NEWNODE(STRING_, env->bucket, (r)))
#define LIST_NEWNODE(u, r)						       \
	(env->bucket.ptr = (u), NEWNODE(LIST_, env->bucket, (r)))
#define FLOAT_NEWNODE(u, r)						       \
	(env->bucket.dbl = (u), NEWNODE(FLOAT_, env->bucket, (r)))
#define FILE_NEWNODE(u, r)						       \
	(env->bucket.ptr = (u), NEWNODE(FILE_, env->bucket, (r)))
#endif
