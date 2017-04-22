/*
    module  : joy.h
    version : 1.11
    date    : 04/22/17
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
extern char **g_argv;
extern int g_argc, error;
extern FILE *outfp, *declfp;
extern unsigned compiling, optimizing, identifier;
extern unsigned autoput, undeferror, echoflag, tracegc;

/* lexer.l */
extern FILE *yyin, *yyout;

/* compile.c */
char *usrname(char *str);
void printstack(FILE *fp);
void initialise(void);
void finalise(void);

/* error.c */
void execerror(char *message, const char *op);

/* history.c */
void add_history(unsigned op);
void add_history2(unsigned op, unsigned op1);
void prt_history(void);
void clr_history(void);
void set_history(int num);
unsigned pop_history(unsigned *op);
unsigned top_history(unsigned *op);
void del_history(int num);
void chg_history(unsigned op);
void chg_history2(unsigned op, unsigned op2);
void *new_history(void);
void old_history(void *save);
void *save_history(void *ptr, unsigned op, unsigned op1);
void swap_history(void *ptr);
int rest_history(void *ptr, unsigned *op, unsigned *op1);

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
