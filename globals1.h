/*
    module  : globals1.h
    version : 1.2
    date    : 05/06/16
*/
#define RUNTIME_CHECKS
/* #define CORRECT_INHAS_COMPARE */
/* #define TRACK_USED_SYMBOLS */

    /* configure */
#define INPSTACKMAX	10
#define INPLINEMAX	1024
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
#ifndef real_t
typedef float		real_t;
#endif
#endif

#ifdef BIT_64
#define SETSIZE		64
#define MAXINT		9223372036854775807LL
#ifndef long_t
typedef long long	long_t;
#endif
#ifndef real_t
typedef double		real_t;
#endif
#endif

    /* symbols from getsym */
#define ILLEGAL_	0
#define COPIED_		1
#define SYMBOL_		1
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
    char *name, *scram;
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
	void (*proc)(void);
    } u;
    struct Entry *next;
} Entry;

#ifdef ALLOC
#define CLASS
#else
#define CLASS extern
#endif

CLASS int g_argc;
CLASS char **g_argv;
CLASS int echoflag;
CLASS int autoput;
CLASS int undeferror;
CLASS int tracegc;
CLASS int startclock;		/* main         */
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
    memory[MEMORYMAX + 1], critical[MEMORYMAX], *crit_ptr;

#ifdef _MSC_VER
Node *stk;
#else
register Node *stk asm("bl");
#endif

/* Public procedures: */

/* interp1.c */
PUBLIC void exeterm(Node *n);
PUBLIC void inisymboltable(void); /* initialise */
PUBLIC char *opername(int o);

/* main1.c */
PUBLIC void gc_(void);
PUBLIC void execerror(char *message, char *op);

/* scan1.c */
PUBLIC void inilinebuffer(void);
PUBLIC void redirect(FILE *fp);
PUBLIC void include(char *filnam);

/* getsym.c */
PUBLIC void getsym(void);

/* utils1.c */
PUBLIC void readfactor(void); /* read a JOY factor */
PUBLIC void readterm(void);
PUBLIC void writefactor(Node *n, FILE *stm);
PUBLIC void writeterm(Node *n, FILE *stm);

#define USR_NEWNODE(u,r)	newnode(USR_, u, r)
#define ANON_FUNCT_NEWNODE(u,r)	newnode(ANON_FUNCT_, u, r)
#define BOOLEAN_NEWNODE(u,r)	newnode(BOOLEAN_, (void *)(u), r)
#define CHAR_NEWNODE(u,r)	newnode(CHAR_, (void *)(long_t)(u), r)
#define INTEGER_NEWNODE(u,r)	newnode(INTEGER_, (void *)(u), r)
#define SET_NEWNODE(u,r)	newnode(SET_, (void *)(u), r)
#define STRING_NEWNODE(u,r)	newnode(STRING_, u, r)
#define LIST_NEWNODE(u,r)	newnode(LIST_, u, r)
#define FLOAT_NEWNODE(u,r)	dblnode(u, r)
#define FILE_NEWNODE(u,r)	newnode(FILE_, u, r)
#define SYM_NEWNODE(u,r)	newnode(SYMBOL_, u, r)

#define OUTSIDE		!inside_condition && !inside_critical
#define RELEASE		if (!--inside_critical) crit_ptr = &critical[MEMORYMAX]
#define CONDITION	++inside_critical

#define DUPLICATE(node)						\
do {								\
    if (OUTSIDE && stk > memory && stk <= &memory[MEMORYMAX]) { \
	stk[-1].op = (node)->op;				\
	stk[-1].u.ptr = (node)->u.ptr;				\
	--stk;							\
    } else							\
	stk = newnode((node)->op, (node)->u.ptr, stk);		\
} while (0)

#define PUSH(type, value)					\
do {								\
    Node my_node;						\
    my_node.op = type;						\
    my_node.u.ptr = (void *)(value);				\
    DUPLICATE(&my_node);					\
} while (0)

#define FLOAT_PUSH(value)					\
do {								\
    Node my_node;						\
    my_node.op = FLOAT_;					\
    my_node.u.dbl = value;					\
    DUPLICATE(&my_node);					\
} while (0)

#define POP(X) X = X->next

#define FLOATABLE						\
    (stk->op == INTEGER_ || stk->op == FLOAT_)
#define FLOATABLE2						\
    ((stk->op == FLOAT_ && stk->next->op == FLOAT_) ||		\
     (stk->op == FLOAT_ && stk->next->op == INTEGER_) ||	\
     (stk->op == INTEGER_ && stk->next->op == FLOAT_))
#define FLOATVAL						\
    (stk->op == FLOAT_ ? stk->u.dbl : (double)stk->u.num)
#define FLOATVAL2						\
    (stk->next->op == FLOAT_ ? stk->next->u.dbl : (double)stk->next->u.num)

#ifdef RUNTIME_CHECKS
#define ONEPARAM(NAME)						\
    if (stk == NULL)						\
	execerror("one parameter",NAME)
#define TWOPARAMS(NAME)						\
    if (stk == NULL || stk->next == NULL)			\
	execerror("two parameters",NAME)
#define THREEPARAMS(NAME)					\
    if (stk == NULL || stk->next == NULL			\
		    || stk->next->next == NULL)			\
	execerror("three parameters",NAME)
#define FOURPARAMS(NAME)					\
    if (stk == NULL || stk->next == NULL			\
		    || stk->next->next == NULL			\
		    || stk->next->next->next == NULL)		\
	execerror("four parameters",NAME)
#define FIVEPARAMS(NAME)					\
    if (stk == NULL || stk->next == NULL			\
		    || stk->next->next == NULL			\
		    || stk->next->next->next == NULL		\
		    || stk->next->next->next->next == NULL)	\
	execerror("five parameters",NAME)
#define ONEQUOTE(NAME)						\
    if (stk->op != LIST_)					\
	execerror("quotation as top parameter",NAME)
#define TWOQUOTES(NAME)						\
    ONEQUOTE(NAME);						\
    if (stk->next->op != LIST_)					\
	execerror("quotation as second parameter",NAME)
#define THREEQUOTES(NAME)					\
    TWOQUOTES(NAME);						\
    if (stk->next->next->op != LIST_)				\
	execerror("quotation as third parameter",NAME)
#define FOURQUOTES(NAME)					\
    THREEQUOTES(NAME);						\
    if (stk->next->next->next->op != LIST_)			\
	execerror("quotation as fourth parameter",NAME)
#define SAME2TYPES(NAME)					\
    if (stk->op != stk->next->op)				\
	execerror("two parameters of the same type",NAME)
#define STRING(NAME)						\
    if (stk->op != STRING_)					\
	execerror("string",NAME)
#define STRING2(NAME)						\
    if (stk->next->op != STRING_)				\
	execerror("string as second parameter",NAME)
#define INTEGER(NAME)						\
    if (stk->op != INTEGER_)					\
	execerror("integer",NAME)
#define INTEGER2(NAME)						\
    if (stk->next->op != INTEGER_)				\
	execerror("integer as second parameter",NAME)
#define CHARACTER(NAME)						\
    if (stk->op != CHAR_)					\
	execerror("character",NAME)
#define INTEGERS2(NAME)						\
    if (stk->op != INTEGER_ || stk->next->op != INTEGER_)	\
	execerror("two integers",NAME)
#define NUMERICTYPE(NAME)					\
    if (stk->op != INTEGER_ && stk->op != CHAR_			\
			    && stk->op != BOOLEAN_)		\
	execerror("numeric",NAME)
#define NUMERIC2(NAME)						\
    if (stk->next->op != INTEGER_ && stk->next->op != CHAR_)	\
	execerror("numeric second parameter",NAME)
#define FLOAT(NAME)						\
    if (!FLOATABLE)						\
	execerror("float or integer",NAME);
#define FLOAT2(NAME)						\
    if (!(FLOATABLE2 || (stk->op == INTEGER_ && stk->next->op == INTEGER_))) \
	execerror("two floats or integers",NAME)
#define FILE(NAME)						\
    if (stk->op != FILE_ || stk->u.fil == NULL)			\
	execerror("file",NAME)
#define CHECKZERO(NAME)						\
    if (stk->u.num == 0)					\
	execerror("non-zero operand",NAME)
#define LIST(NAME)						\
    if (stk->op != LIST_)					\
	execerror("list",NAME)
#define LIST2(NAME)						\
    if (stk->next->op != LIST_)					\
	execerror("list as second parameter",NAME)
#define USERDEF(NAME)						\
    if (stk->op != USR_)					\
	execerror("user defined symbol",NAME)
#define CHECKLIST(OPR,NAME)					\
    if (OPR != LIST_)						\
	execerror("internal list",NAME)
#define CHECKSETMEMBER(NODE,NAME)				\
    if ((NODE->op != INTEGER_ && NODE->op != CHAR_) ||		\
	NODE->u.num >= SETSIZE)					\
	execerror("small numeric",NAME)
#define CHECKEMPTYSET(SET,NAME)					\
    if (SET == 0)						\
	execerror("non-empty set",NAME)
#define CHECKEMPTYSTRING(STRING,NAME)				\
    if (!STRING || *STRING == '\0')				\
	execerror("non-empty string",NAME)
#define CHECKEMPTYLIST(LIST,NAME)				\
    if (LIST == NULL)						\
	execerror("non-empty list",NAME)
#define INDEXTOOLARGE(NAME)					\
    execerror("smaller index",NAME)
#define BADAGGREGATE(NAME)					\
    execerror("aggregate parameter",NAME)
#define BADDATA(NAME)						\
    execerror("different type",NAME)
#else
#define ONEPARAM(NAME)
#define TWOPARAMS(NAME)
#define THREEPARAMS(NAME)
#define FOURPARAMS(NAME)
#define FIVEPARAMS(NAME)
#define ONEQUOTE(NAME)
#define TWOQUOTES(NAME)
#define THREEQUOTES(NAME)
#define FOURQUOTES(NAME)
#define SAME2TYPES(NAME)
#define STRING(NAME)
#define STRING2(NAME)
#define INTEGER(NAME)
#define INTEGER2(NAME)
#define CHARACTER(NAME)
#define INTEGERS2(NAME)
#define NUMERICTYPE(NAME)
#define NUMERIC2(NAME)
#define FLOAT(NAME)
#define FLOAT2(NAME)
#define FILE(NAME)
#define CHECKZERO(NAME)
#define LIST(NAME)
#define LIST2(NAME)
#define USERDEF(NAME)
#define CHECKLIST(OPR,NAME)
#define CHECKSETMEMBER(NODE,NAME)
#define CHECKEMPTYSET(SET,NAME)
#define CHECKEMPTYSTRING(STRING,NAME)
#define CHECKEMPTYLIST(LIST,NAME)
#define INDEXTOOLARGE(NAME) {}
#define BADAGGREGATE(NAME)
#define BADDATA(NAME)
#endif

#define NULLARY(CONSTRUCTOR,VALUE)                              \
    stk = CONSTRUCTOR((VALUE),stk)
#define UNARY(CONSTRUCTOR,VALUE)                                \
    stk = CONSTRUCTOR((VALUE),stk->next)
#define BINARY(CONSTRUCTOR,VALUE)                               \
    stk = CONSTRUCTOR((VALUE),stk->next->next)
#define GNULLARY(TYPE,VALUE)                                    \
    stk = newnode(TYPE,(void *)(VALUE),stk)
#define GUNARY(TYPE,VALUE)                                      \
    stk = newnode(TYPE,(void *)(VALUE),stk->next)
#define GBINARY(TYPE,VALUE)                                     \
    stk = newnode(TYPE,(void *)(VALUE),stk->next->next)
#define GTERNARY(TYPE,VALUE)					\
    stk = newnode(TYPE,(void *)(VALUE),stk->next->next->next)

#define PUSH_PROC(PROCEDURE,CONSTRUCTOR,VALUE)			\
PRIVATE void PROCEDURE(void)					\
{ PUSH(CONSTRUCTOR,VALUE); }

#define USETOP(PROCEDURE,NAME,TYPE,BODY)			\
PRIVATE void PROCEDURE(void)					\
{ ONEPARAM(NAME); TYPE(NAME); BODY; POP(stk); }
