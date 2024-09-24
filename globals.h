/*
    module  : globals.h
    version : 1.56
    date    : 09/24/24
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
#define WIN32_LEAN_AND_MEAN
#include <windows.h>		/* pollute name space as much as possible */
#include <io.h>			/* also import deprecated POSIX names */
#pragma warning(disable: 4244 4267 4996)
#define kh_packed		/* forget about __attribute__ ((packed)) */
#else
#include <unistd.h>		/* alarm function */
#include <termios.h>
#include <sys/ioctl.h>
#endif

/*
 * The following #defines are present in the source code.
 */
#if 0
#define USE_BIGNUM_ARITHMETIC
#define USE_MULTI_THREADS_JOY
#endif

#define USE_KHASHL

#ifdef _MSC_VER
#include "../joy1/gc-8.2.8/include/gc.h"
#else
#include <gc.h>			/* system installed BDW */
#endif
#include "kvec.h"
#include "khashl.h"
#ifdef USE_BIGNUM_ARITHMETIC
#include "bignum.h"
#endif

/* configure			*/
#define INPSTACKMAX	10
#define INPLINEMAX	255
#define BUFFERMAX	80	/* smaller buffer */
#define HELPLINEMAX	72
#define MAXNUM		40	/* even smaller buffer */
#define FILENAMEMAX	14
#define DISPLAYMAX	10	/* nesting in HIDE & MODULE */
#define INIECHOFLAG	0
#define INIAUTOPUT	1
#define INITRACEGC	1
#define INIUNDEFERROR	0
#define INIWARNING	0

/* installation dependent	*/
#define SETSIZE (int)(CHAR_BIT * sizeof(uint64_t))	/* from limits.h */
#define MAXINT_ INT64_MAX				/* from stdint.h */

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
    SIZE_,
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
    IN_,
    HAS,
    CASE,
    FIRST,
    OF,
    AT,
    DIV,
    REM,
    DIVIDE,
    FWRITE,
    ASSIGN,
#ifdef USE_MULTI_THREADS_JOY
    RECEIVE,
    SEND
#endif
} Params;

typedef enum {
    OK,
    IGNORE_OK,
    IGNORE_PUSH,
    IGNORE_POP,
    IMMEDIATE,
    POSTPONE
} Flags;

typedef enum {
    ABORT_NONE,
    ABORT_RETRY,
    ABORT_ERROR,
    ABORT_QUIT
} Abort;

/* types			*/
typedef int Symbol;		/* symbol created by scanner */

typedef struct Env *pEnv;	/* pointer to global variables */

typedef void (*proc_t)(pEnv);	/* procedure */

typedef vector(struct Node) *NodeList;	/* forward */

typedef unsigned char Operator;	/* opcode / datatype */

/*
 * Lists are stored in vectors of type Node.
 */
#include "pars.h"		/* YYSTYPE */

/*
 * Nodes are in consecutive memory locations. No next pointer needed.
 */
typedef struct Node {
    YYSTYPE u;
    Operator op;
} Node;

#ifdef USE_MULTI_THREADS_JOY
#include "task.h"
#endif

/*
 * The symbol table has a name/value pair. Type of value depends on is_user.
 * The flags are used to distinguish between immediate and normal functions.
 */
typedef struct Entry {
    char *name, is_user, flags;
    union {
	NodeList body;
	proc_t proc;
    } u;
} Entry;

typedef struct Token {
    YYSTYPE yylval;
    Symbol symb;
} Token;

/*
 * The symbol table is accessed through two hash tables, one with name as
 * index; the other with function address as index, cast to uint64_t.
 */
KHASHL_MAP_INIT(KH_LOCAL, symtab_t, symtab, kh_cstr_t, int, kh_hash_str,
		kh_eq_str)
KHASHL_MAP_INIT(KH_LOCAL, funtab_t, funtab, uint64_t, int, kh_hash_uint64,
		kh_eq_generic)

/*
 * Global variables are stored locally in the main function.
 */
typedef struct Env {
    jmp_buf finclude;		/* return point in finclude */
    double calls;		/* statistics */
    double opers;
    vector(Token) *tokens;	/* read ahead table */
    vector(Entry) *symtab;	/* symbol table */
#ifdef USE_MULTI_THREADS_JOY
    vector(Context) *context;
    vector(Channel) *channel;
#endif
    symtab_t *hash;		/* hash tables that index the symbol table */
    funtab_t *prim;
    NodeList stck, prog;	/* stack, code, and quotations are vectors */
    clock_t startclock;		/* main */
    char **g_argv;
    char *homedir;		/* HOME or HOMEPATH */
    char *filename;		/* first include file */
    vector(char *) *pathnames;	/* pathnames to be searched when including */
    int g_argc;
    int token;			/* yylex */
#ifdef USE_BIGNUM_ARITHMETIC
    int scale;			/* number of digits after the decimal point */
#endif
#ifdef USE_MULTI_THREADS_JOY
    int current;		/* currently executing thread */
#endif
    int hide_stack[DISPLAYMAX];
    struct {
	char *name;
	int hide;
    } module_stack[DISPLAYMAX];
    unsigned char inlining;
    unsigned char autoput;	/* options */
    unsigned char autoput_set;
    unsigned char echoflag;
    unsigned char tracegc;
    unsigned char undeferror;
    unsigned char undeferror_set;
    unsigned char alarming;
    unsigned char bytecoding;
    unsigned char compiling;
    unsigned char debugging;
    unsigned char ignore;
    unsigned char overwrite;
    unsigned char printing;
    unsigned char recurse;
    unsigned char finclude_busy;
} Env;

typedef struct table_t {
    proc_t proc;
    char *name;
} table_t;

/* Public procedures: */
/* arty.c */
int arity(pEnv env, NodeList quot, int num);
/* eval.c */
void trace(pEnv env, FILE *fp);
void evaluate(pEnv env, NodeList list);
/* exec.c */
void execute(pEnv env, NodeList list);
/* exeterm.c */
void exeterm(pEnv env, NodeList list);
/* lexr.l */
void new_buffer(void);
void old_buffer(int num);
int my_yylex(pEnv env);
int get_input(void);
/* main.c */
void abortexecution_(int num);
/* modl.c */
void savemod(int *hide, int *modl, int *hcnt);
void undomod(int hide, int modl, int hcnt);
void initmod(pEnv env, char *name);
void initpriv(pEnv env);
void stoppriv(void);
void exitpriv(void);
void exitmod(void);
char *classify(pEnv env, char *name);
int qualify(pEnv env, char *name);
/* otab.c */
char *showname(int i);
int operindex(pEnv env, proc_t proc);
char *opername(pEnv env, proc_t proc);
char *cmpname(pEnv env, proc_t proc);
char *operarity(int i);
int tablesize(void);
int operqcode(int index);
void inisymboltable(pEnv env);	/* initialise */
/* parm.c */
void parm(pEnv env, int num, Params type, char *file);
/* print.c */
void print(pEnv env);
/* prog.c */
void prog(pEnv env, NodeList list);
void code(pEnv env, proc_t proc);
void push(pEnv env, int64_t num);
void prime(pEnv env, Node node);
Node pop(pEnv env);
/* read.c */
int readfactor(pEnv env);	/* read a JOY factor */
void readterm(pEnv env);
/* repl.c */
int lookup(pEnv env, char *name);
void enteratom(pEnv env, char *name, NodeList list);
NodeList newnode(Operator op, YYSTYPE u);
/* save.c */
void save(pEnv env, NodeList list, int num, int remove);
/* scan.c */
void inilinebuffer(pEnv env);
int include(pEnv env, char *str);
int my_yywrap(pEnv env);	/* yywrap replacement */
void my_error(char *str, YYLTYPE *bloc);
void yyerror(pEnv env, char *str);
/* util.c */
int ChrVal(pEnv env, char *str);
char *StrVal(pEnv env, char *str);
/* writ.c */
void writefactor(pEnv env, Node node, FILE *fp);
void writeterm(pEnv env, NodeList list, FILE *fp);
void writestack(pEnv env, NodeList list, FILE *fp);
/* xerr.c */
void execerror(char *message, char *op);
/* ylex.c */
int yylex(pEnv env);
/* byte.c */
void initbytes(pEnv env);
void bytecode(pEnv env, NodeList list);
void exitbytes(pEnv env);
/* code.c */
void readbyte(pEnv env, FILE *fp, int flag);
unsigned char *readfile(FILE *fp);
/* comp.c */
void initcompile(pEnv env);
void exitcompile(pEnv env);
int compile(pEnv env, NodeList list);
/* dump.c */
void dumpbyte(pEnv env, FILE *fp);
/* optm.c */
void optimize(pEnv env, FILE *fp);
/* kraw.c */
void SetRaw(pEnv env);
#endif
