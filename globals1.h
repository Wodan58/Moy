/*
    module  : globals1.h
    version : 1.1
    date    : 12/27/15
*/
/* #define CORRECT_INHAS_COMPARE */
/* #define TRACK_USED_SYMBOLS */

    /* configure */
#define SHELLESCAPE	'$'
#define INPSTACKMAX	10
#define INPLINEMAX	1024
#define FLOAT_BUFFER	320
#define ALEN		22
#define HASHSIZE	9
#define SYMTABMAX	1000
#define DISPLAYMAX	10	/* nesting in HIDE & MODULE */
#define MEMORYMAX	1000
#define INIECHOFLAG	0
#define INIAUTOPUT	1
#define INITRACEGC	1

    /* installation dependent */
#ifdef BIT_32
#define SETSIZE		32
#define MAXINT		2147483647
#ifndef long_t
typedef long		long_t;
#endif
#else
#define SETSIZE		64
#define MAXINT		9223372036854775807LL
#ifndef long_t
typedef long long	long_t;
#endif
#endif

    /* symbols from getsym */
#define ILLEGAL_	0
#define COPIED_		1
#define USR_		2
#define ANON_FUNCT_	3
#define BOOLEAN_	4
#define CHAR_		5
#define INTEGER_	6
#define SET_		7
#define STRING_		8
#define LIST_		9
#define FLOAT_		10
#define FILE_		11
#define FALSE_		12
#define TRUE_		13
#define MAXINT_		14
#define ATOM		999	/* last legal factor begin */

#define PRIVATE
#define PUBLIC

    /* types */
#include "joy.h"

typedef struct Node {
    Types u;
    Operator op, type;
    struct Node *next;
} Node;

typedef struct Entry {
    char *name;
    unsigned char is_module;
    unsigned char is_local;
    unsigned char is_unknown;
    unsigned char is_expanding;
#ifdef TRACK_USED_SYMBOLS
    unsigned char is_used;
#endif
    union {
	Node *body;
	struct Entry *module_fields;
	void (*proc)();
    } u;
    struct Entry *next;
} Entry;

#ifdef ALLOC
#define CLASS
#else
#define CLASS extern
#endif

#if 0
CLASS FILE *srcfile;
#endif
CLASS int g_argc;
CLASS char **g_argv;
CLASS int echoflag;
CLASS int autoput;
CLASS int undeferror;
CLASS int tracegc;
CLASS int startclock, gc_clock;	/* main         */
CLASS int ch;			/* scanner      */
CLASS int sym;
CLASS long_t num;
CLASS double dbl;
CLASS char id[ALEN];
CLASS int hashvalue;
CLASS Types bucket;		/* used by NEWNODE defines */
CLASS int display_enter;
CLASS int display_lookup;

CLASS int inside_condition;
CLASS int inside_critical;
CLASS int inside_definition;

CLASS Entry /* symbol table */
    symtab[SYMTABMAX], *hashentry[HASHSIZE],
    *symtabindex, *display[DISPLAYMAX], *firstlibra, /* inioptable */
    *location; /* getsym */

CLASS Node /* dynamic memory */
    memory[MEMORYMAX], *stk, critical[MEMORYMAX], *crit_ptr;

#define tmp_release()	crit_ptr = &critical[MEMORYMAX]

/* GOOD REFS:
	005.133l H4732		A LISP interpreter in C
	Manna p139  recursive Ackermann SCHEMA

   OTHER DATA TYPES
	WORD = "ABCD" - up to four chars
	LIST of SETs of char [S0 S1 S2 S3]
	        LISTS - binary tree [left right]
			" with info [info left right]
	STRING of 32 chars = 32 * 8 bits = 256 bits = bigset
	CHAR = 2 HEX
	32 SET = 2 * 16SET
*/

/* Public procedures: */
PUBLIC void exeterm(Node * n);
PUBLIC void inisymboltable(void); /* initialise */
PUBLIC char *opername(int o);
PUBLIC void HashValue(char *str);
PUBLIC void lookup(void);
PUBLIC void abortexecution_(void);
PUBLIC void execerror(char *message, char *op);
PUBLIC void quit_(void);
PUBLIC void inilinebuffer(void);
#if 0
PUBLIC void putline(void);
PUBLIC int endofbuffer(void);
PUBLIC void error(char *message);
#endif
PUBLIC void redirect(FILE *);
PUBLIC void doinclude(char *filnam);
PUBLIC void getsym(void);
#if 0
PUBLIC void inimem1(void);
PUBLIC void inimem2(void);
PUBLIC void printnode(Node *p);
#endif
PUBLIC void gc_(void);
PUBLIC Node *newnode(Operator o, Types u, Node * r);
#if 0
PUBLIC void memoryindex_(void);
#endif
PUBLIC void readfactor(void); /* read a JOY factor */
PUBLIC void readterm(void);
PUBLIC void writefactor(Node *n, FILE *stm);
PUBLIC void writeterm(Node *n, FILE *stm);

#define USR_NEWNODE(u,r)	(bucket.ent = u, newnode(USR_, bucket, r))
#define ANON_FUNCT_NEWNODE(u,r)	(bucket.proc= u, newnode(ANON_FUNCT_,bucket,r))
#define BOOLEAN_NEWNODE(u,r)	(bucket.num = u, newnode(BOOLEAN_, bucket, r))
#define CHAR_NEWNODE(u,r)	(bucket.num = u, newnode(CHAR_, bucket, r))
#define INTEGER_NEWNODE(u,r)	(bucket.num = u, newnode(INTEGER_, bucket, r))
#define SET_NEWNODE(u,r)	(bucket.num = u, newnode(SET_, bucket, r))
#define STRING_NEWNODE(u,r)	(bucket.str = u, newnode(STRING_, bucket, r))
#define LIST_NEWNODE(u,r)	(bucket.lis = u, newnode(LIST_, bucket, r))
#define FLOAT_NEWNODE(u,r)	(bucket.dbl = u, newnode(FLOAT_, bucket, r))
#define FILE_NEWNODE(u,r)	(bucket.fil = u, newnode(FILE_, bucket, r))

#define DUPLICATE(node)						\
do {								\
    if (!inside_condition && !inside_critical && !stk)		\
	stk = &memory[MEMORYMAX];				\
    if (!inside_condition && !inside_critical &&		\
	     stk > memory && stk <= &memory[MEMORYMAX]) {	\
	stk[-1].op = (node)->op;				\
	stk[-1].u = (node)->u;					\
	--stk;							\
    } else							\
	stk = newnode((node)->op, (node)->u, stk);		\
} while (0)

#define PUSH(type, value)					\
do {								\
    Node my_node;						\
    my_node.op = (type);					\
    my_node.u = (Types) (value);				\
    DUPLICATE(&my_node);					\
} while (0)

#define POP(X) X = X->next

#define OUTSIDE		!inside_condition && !inside_critical
