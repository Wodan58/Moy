/*
    module  : symbol.h
    version : 1.1
    date    : 03/12/17
*/
#define ALEN		22
#define SYMTABMAX	500
#define INPLINEMAX	1000

#define IS_MODULE	1
#define IS_LOCAL	2
#define IS_UNKNOWN	4
#define IS_USED		8
#define IS_PRINTED	16
#define IS_BUILTIN	32
#define IS_ACTIVE	64

#define MID_SCOPE	0
#define START_SCOPE	1
#define END_SCOPE	2
#define INIT_SCOPE	3
#define STOP_SCOPE	4

typedef unsigned Operator;

typedef struct Node {
    YYSTYPE u;
    Operator op;
    struct Node *next;
} Node;

typedef struct Entry {
    char *name;
    unsigned flags;
    union {
	Node *body;
	void (*proc)(void);
	struct Entry *member;
    } u;
    struct Entry *next;
} Entry;

/* symbol.c */
extern Entry symtab[];
extern unsigned symtabindex;

/* compile.c */
unsigned PrintHead(Node *node, FILE *fp);

/* interp.c */
void interprete(Node *code);
void execute(Node *code);
void evaluate(Node *code);
void evaluate1(Node *code);
void evaluate2(Node *code, int num);

#include "node.h"

/* print.c */
char *opername(int num);
char *printname(int num);
char *procname(void (*proc)(void));
void writefactor(Node *node, FILE *stm);
void writeterm(Node *code, FILE *stm);
void writestack(Node *code, FILE *stm);

/* symbol.c */
Entry *lookup(char *name);
Entry *enteratom(Entry *sym, Node *body);
Entry *initmod(Entry *sym);
void exitmod(Entry *sym);
Entry *initpriv(void);
void stoppriv(void);
void exitpriv(Entry *prev);
void dump(void);
