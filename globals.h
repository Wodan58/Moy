/*
    module  : globals.h
    version : 1.6
    date    : 08/21/23
*/
#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <setjmp.h>
#include <inttypes.h>

#ifdef _MSC_VER
#include <io.h>
#pragma warning(disable : 4244 4267 4996)
#else
#include <unistd.h>
#endif

/*
    The following #defines are present in the source code.
*/
#define BDW_GARBAGE_COLLECTOR    /* main.c */
#if 0
#define USE_BIGNUM_ARITHMETIC
#endif

#include <gc.h>                  /* system installed BDW or local gc.h */
#include "khash.h"
#ifdef USE_BIGNUM_ARITHMETIC
#include "bignum.h"
#endif

/* configure                     */
#define INPSTACKMAX 10
#define INPLINEMAX 255
#define BUFFERMAX 80
#define DISPLAYMAX 10            /* nesting in HIDE & MODULE */
#define INIECHOFLAG 0
#define INIAUTOPUT 1
#define INIUNDEFERROR 0
#define INIWARNING 1

/* installation dependent        */
#define SETSIZE 64
#define MAXINT 9223372036854775807LL

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
    HAS,
    CASE,
    FIRST,
    OF,
    AT,
    DIV,
    REM,
    DIVIDE,
    FWRITE
} Params;

typedef enum {
    OK,
    IMMEDIATE
} Flags;

#define PRIVATE
#define PUBLIC

/* types                         */
typedef int Symbol;              /* symbol created by scanner */

typedef struct Env *pEnv;        /* pointer to global variables */

typedef void (*proc_t)(pEnv);    /* procedure */

typedef struct NodeList NodeList;/* forward */

typedef int pEntry;              /* index in symbol table */

typedef unsigned char Operator;  /* opcode / datatype */

/*
    Lists are stored in vectors of type Node.
*/
#include "pars.h"

/*
    Nodes are in consecutive memory locations. No next pointer needed.
*/
typedef struct Node {
    YYSTYPE u;
    Operator op;
} Node;

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

#include "list.h"          /* nodelist */
#include "syml.h"          /* symlist */
#include "tokl.h"	   /* tokenlist */

/*
    Global variables are stored locally in the main function.
*/
typedef struct Env {
    TokList *tokens;       /* read ahead table */
    NodeList *stck, *prog; /* both stack and code are stored in vectors */
    SymList *symtab;       /* symbol table */
    khash_t(Symtab) *hash;
    clock_t startclock;    /* main */
    char *pathname;
    char **g_argv;
    int g_argc;
    int token;             /* yylex */
    pEntry location;       /* lookup */
    char *hide_stack[DISPLAYMAX];
    struct module {
        char *name;
        int hide;
    } module_stack[DISPLAYMAX];
    unsigned char autoput; /* options */
    unsigned char echoflag;
    unsigned char undeferror;
    unsigned char tracegc;
    unsigned char debugging;
    unsigned char overwrite;
    unsigned char nothing;
} Env;

typedef struct OpTable {
    char flags;
    char *name;
    proc_t proc;
    char *arity, *messg1, *messg2;
} OpTable;

/* Public procedures: */
/* eval.c */
PUBLIC void exeterm(pEnv env);
PUBLIC char *nickname(int o);
PUBLIC char *showname(int o);
PUBLIC int operindex(proc_t proc);
PUBLIC char *cmpname(proc_t proc);
PUBLIC char *opername(proc_t proc);
PUBLIC char *operarity(proc_t proc);
PUBLIC proc_t operproc(int o);
PUBLIC OpTable *readtable(int o);
/* repl.c */
PUBLIC void inisymboltable(pEnv env); /* initialise */
PUBLIC void lookup(pEnv env, char *name);
PUBLIC void enteratom(pEnv env, char *name, NodeList *list);
PUBLIC void execute(pEnv env, NodeList *list);
PUBLIC NodeList *newnode(Operator op, YYSTYPE u);
PUBLIC void reverse(NodeList *list);
/* main.c */
PUBLIC void abortexecution_(void);
PUBLIC void execerror(char *message, char *op);
/* quit.c */
PUBLIC void my_atexit(proc_t proc);
PUBLIC void quit_(pEnv env);
/* comp.c */
PUBLIC int Compare(pEnv env, Node first, Node second);
/* manl.c */
PUBLIC void make_manual(int style /* 0=plain, 1=HTML, 2=Latex */);
/* dtim.c */
PUBLIC void dtime(Node node, struct tm *t);
/* arty.c */
PUBLIC int arity(pEnv env, NodeList *quot, int num);
/* save.c */
PUBLIC void save(pEnv env, NodeList *quot, int num);
/* undo.c */
PUBLIC void undo(pEnv env, NodeList *quot, int num);
/* parm.c */
PUBLIC void parm(pEnv env, int num, Params op, char *file);
/* prog.c */
PUBLIC void prog(pEnv env, NodeList *list);
PUBLIC void code(pEnv env, proc_t proc);
PUBLIC void push(pEnv env, int64_t num);
PUBLIC void prime(pEnv env, Node node);
PUBLIC Node pop(pEnv env);
/* scan.c */
PUBLIC void inilinebuffer(char *filnam);
PUBLIC int yyerror(pEnv env, char *message);
PUBLIC void my_error(pEnv env, char *message, YYLTYPE *bloc);
PUBLIC int include(pEnv env, char *filnam, int error);
int yywrap(void);
/* lexr.l */
int getnextchar(void);
void new_buffer(void);
void old_buffer(int num);
int my_yylex(pEnv env);
/* ylex.c */
void ungetsym(Symbol sym);
int yylex(pEnv env);
/* util.c */
PUBLIC int ChrVal(char *str);
PUBLIC char *StrVal(char *str);
PUBLIC char *DelSpace(char *str);
/* read.c */
PUBLIC void readfactor(pEnv env); /* read a JOY factor */
PUBLIC void readterm(pEnv env);
/* writ.c */
PUBLIC void writefactor(pEnv env, Node node);
PUBLIC void writeterm(pEnv env, NodeList *list);
PUBLIC void writestack(pEnv env, NodeList *list);
/* modl.c */
PUBLIC void savemod(int *hide, int *modl);
PUBLIC void undomod(int hide, int modl);
PUBLIC void initmod(pEnv env, char *name);
PUBLIC void initpriv(pEnv env);
PUBLIC void stoppriv(void);
PUBLIC void exitpriv(void);
PUBLIC void exitmod(void);
PUBLIC char *classify(pEnv env, char *name);
PUBLIC pEntry qualify(pEnv env, char *name);
#endif
