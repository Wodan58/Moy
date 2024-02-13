/*
    module  : globals.h
    version : 1.32
    date    : 02/12/24
*/
#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>
#include <signal.h>
#include <math.h>
#include <time.h>
#include <inttypes.h>

#ifdef _MSC_VER
#pragma warning(disable: 4244 4267)
#else
#include <unistd.h>		/* alarm function */
#endif

/*
    The following #defines are present in the source code.
*/
#if 0
#define USE_BIGNUM_ARITHMETIC
#define USE_MULTI_THREADS_JOY
#define WRITE_USING_RECURSION
#endif

#include <gc.h>			/* system installed BDW or local gc.h */
#include "khash.h"
#include "kvec.h"
#ifdef USE_BIGNUM_ARITHMETIC
#include "bignum.h"
#endif

/* configure			*/
#define INPSTACKMAX 10
#define INPLINEMAX 255
#define BUFFERMAX 80
#define DISPLAYMAX 10		/* nesting in HIDE & MODULE */
#define INIECHOFLAG 0
#define INIAUTOPUT 1
#define INIUNDEFERROR 0
#define INIWARNING 1

/* installation dependent	*/
#define SETSIZE (int)(CHAR_BIT * sizeof(uint64_t))	/* from limits.h */
#define MAXINT INT64_MAX				/* from stdint.h */

typedef enum {
    ANYTYPE,
    DIP,
    WHILE,
    IFTE,
    LINREC,
    HELP,
    INFRA,
    UFLOAT,
    MUL,
    BFLOAT,
    FGET,
    FPUT,
    STRFTIME,
    FPUTCHARS,
    STRTOD,
    FOPEN,
    UNMKTIME,
    FREAD,
    LDEXP,
    STRTOL,
    FSEEK,
    TIMES,
    MAXMIN,
    PREDSUCC,
    PLUSMINUS,
    SIZE,
    STEP,
    TAKE,
    CONCAT,
    ANDORXOR,
    NOT,
    PRIMREC,
    SMALL,
    BODY,
    INTERN,
    FORMAT,
    FORMATF,
    CONS,
    IN,
    HAS,
    CASE,
    FIRST,
    OF,
    AT,
    DIV,
    REM,
    DIVIDE,
    FWRITE,
    RECEIVE,
    SEND
} Params;

typedef enum {
    NOT_USED,
    MY_ABORT,
    PARS_ERR,
    EXEC_ERR,
    QUIT_ERR
} Aborts;

typedef enum {
    OK,
    IMMEDIATE
} Flags;

#define PRIVATE
#define PUBLIC

/* types			*/
typedef int Symbol;			/* symbol created by scanner */

typedef struct Env *pEnv;		/* pointer to global variables */

typedef void (*proc_t)(pEnv);		/* procedure */

typedef struct NodeList NodeList;	/* forward */

typedef int pEntry;			/* index in symbol table */

typedef unsigned char Operator;		/* opcode / datatype */

/*
    Lists are stored in vectors of type Node.
*/
#include "pars.h"	/* YYSTYPE */

/*
    Nodes are in consecutive memory locations. No next pointer needed.
*/
typedef struct Node {
    YYSTYPE u;
    Operator op;
} Node;

#include "pvec.h"	/* struct NodeList */

#ifdef USE_MULTI_THREADS_JOY
#include "task.h"
#endif

/*
    The symbol table has a name/value pair. Type of value depends on is_user.
    The flags are used to distinguish between immediate and normal functions.
*/
typedef struct Entry {
    char *name, is_user, flags;
    union {
	NodeList *body;
	proc_t proc;
    } u;
} Entry;

typedef struct Token {
    YYSTYPE yylval;
    Symbol symb;
} Token;

/*
    The symbol table is accessed through a hash table.
*/
KHASH_MAP_INIT_STR(Symtab, pEntry)

/*
    Global variables are stored locally in the main function.
*/
typedef struct Env {
    vector(Token) *tokens;	/* read ahead table */
    vector(Entry) *symtab;	/* symbol table */
#ifdef USE_MULTI_THREADS_JOY
    vector(Context) *context;
    vector(Channel) *channel;
#endif
    khash_t(Symtab) *hash;
    NodeList *stck, *prog;	/* stack, code, and quotations are vectors */
    clock_t startclock;		/* main */
    char *pathname;
    char *filename;
    char *output;		/* output file/function */
    char **g_argv;
    int g_argc;
    int token;			/* yylex */
    pEntry location;		/* lookup */
#ifdef USE_BIGNUM_ARITHMETIC
    int radix;			/* output radix */
    int scale;			/* number of digits after the decimal point */
#endif
#ifdef USE_MULTI_THREADS_JOY
    int current;		/* currently executing thread */
#endif
    int maximum;		/* maximum limit of data and code */
    int operats;		/* limit to number of operations */
    int hide_stack[DISPLAYMAX];
    struct module {
	char *name;
	int hide;
    } module_stack[DISPLAYMAX];
    unsigned char autoput;	/* options */
    unsigned char autoput_set;
    unsigned char echoflag;
    unsigned char echoflag_set;
    unsigned char undeferror;
    unsigned char undeferror_set;
    unsigned char tracegc;
    unsigned char debugging;
    unsigned char ignore;
    unsigned char overwrite;
    unsigned char compiling;
    unsigned char bytecoding;
    unsigned char statistics;
    unsigned char keyboard;
    unsigned char preserve;
    unsigned char quiet;
    unsigned char norecurse;
    unsigned char alarming;
} Env;

typedef struct OpTable {
    char flags;
    char *name;
    proc_t proc;
    char *arity, *messg1, *messg2;
} OpTable;

typedef struct table_t {
    proc_t proc;
    char *name;
} table_t;

/* Public procedures: */
/* arty.c */
PUBLIC int arity(pEnv env, NodeList *quot, int num);
/* comp.c */
PUBLIC void initcompile(pEnv env);
PUBLIC void compileprog(pEnv env, NodeList *list);
/* eval.c */
PUBLIC void exeterm(pEnv env, NodeList *list);
PUBLIC char *showname(int i);
PUBLIC int operindex(proc_t proc);
PUBLIC char *cmpname(proc_t proc);
PUBLIC char *opername(proc_t proc);
PUBLIC char *operarity(proc_t proc);
/* exec.c */
PUBLIC void execute(pEnv env, NodeList *list);
/* lexr.l */
PUBLIC void do_putline(pEnv env, char *str, int line);
PUBLIC void new_buffer(void);
PUBLIC void old_buffer(int num);
PUBLIC int my_yylex(pEnv env);
PUBLIC int get_input(void);
/* main.c */
PUBLIC void abortexecution_(int num);
/* modl.c */
PUBLIC void savemod(int *hide, int *modl, int *hcnt);
PUBLIC void undomod(int hide, int modl, int hcnt);
PUBLIC void initmod(pEnv env, char *name);
PUBLIC void initpriv(pEnv env);
PUBLIC void stoppriv(void);
PUBLIC void exitpriv(void);
PUBLIC void exitmod(void);
PUBLIC char *classify(pEnv env, char *name);
PUBLIC pEntry qualify(pEnv env, char *name);
/* otab.c */
PUBLIC OpTable *readtable(int i);
PUBLIC int tablesize(void);
/* parm.c */
PUBLIC void parm(pEnv env, int num, Params type, char *file);
/* prog.c */
PUBLIC void prog(pEnv env, NodeList *list);
PUBLIC void code(pEnv env, proc_t proc);
PUBLIC void push(pEnv env, int64_t num);
PUBLIC void prime(pEnv env, Node node);
PUBLIC Node pop(pEnv env);
/* read.c */
PUBLIC void readfactor(pEnv env) /* read a JOY factor */;
PUBLIC void readterm(pEnv env);
/* repl.c */
PUBLIC void inisymboltable(pEnv env) /* initialise */;
PUBLIC void lookup(pEnv env, char *name);
PUBLIC void enteratom(pEnv env, char *name, NodeList *list);
PUBLIC NodeList *newnode(Operator op, YYSTYPE u);
/* save.c */
PUBLIC void save(pEnv env, NodeList *list, int num, int remove);
/* scan.c */
PUBLIC void inilinebuffer(pEnv env, int joy);
PUBLIC void include(pEnv env, char *str);
PUBLIC int yywrap(void);
PUBLIC void my_error(char *str, YYLTYPE *bloc);
PUBLIC int yyerror(pEnv env, char *str);
/* util.c */
PUBLIC int ChrVal(pEnv env, char *str);
PUBLIC char *StrVal(pEnv env, char *str);
/* writ.c */
PUBLIC void writefactor(pEnv env, Node node, FILE *fp);
PUBLIC void writeterm(pEnv env, NodeList *list, FILE *fp);
PUBLIC void writestack(pEnv env, NodeList *list, FILE *fp);
/* xerr.c */
PUBLIC void execerror(char *filename, char *message, char *op);
/* ylex.c */
PUBLIC int yylex(pEnv env);
/* quit.c */
PUBLIC void my_atexit(proc_t proc);
PUBLIC void quit_(pEnv env);
/* byte.c */
PUBLIC void initbytes(pEnv env);
PUBLIC void bytecode(NodeList *list);
/* code.c */
PUBLIC void readbytes(pEnv env);
/* dump.c */
PUBLIC void dumpbytes(pEnv env);
#endif
