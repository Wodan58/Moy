/*
    module  : symbol.h
    version : 1.4
    date    : 06/28/18
*/
#define ALEN		22
#define SYMTABMAX	700
#define INPLINEMAX	1000

#define IS_MODULE	1
#define IS_LOCAL	2
#define IS_UNKNOWN	4
#define IS_USED		8
#define IS_PRINTED	16
#define IS_BUILTIN	32
#define IS_ACTIVE	64
#define IS_MARKED	128
#define IS_DECLARED	256

#define MID_SCOPE	0
#define START_SCOPE	1
#define END_SCOPE	2
#define INIT_SCOPE	3
#define STOP_SCOPE	4

typedef unsigned char Operator;

typedef struct Node {
    YYSTYPE u;
    Operator op;
    struct Node *next;
} Node;

typedef void (*proc_t)(void);

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
void writefactor(Node *node, FILE *stm);
void writeterm(Node *code, FILE *stm);
void writestack(Node *code, FILE *stm);

/* symbol.c */
void initmod(char *str);
void exitmod(void);
void initpriv(void);
void stoppriv(void);
void exitpriv(void);
char *prefix(int *hide, int *local);
char *iterate(char *name);

/* dict.c */
void init_dict(void);
int lookup(char *name);
void enteratom(char *name, Node *cur);
void dump(void);
unsigned dict_flags(int index);
void dict_setflags(int index, unsigned flags);
char *dict_name(int index);
char *dict_nickname(int index);
Node *dict_body(int index);
int dict_size(void);
char *dict_descr(int index);
int check_anything_was_printed(void);
void iterate_dict_and_write_struct(void);

char *procname(proc_t proc);
proc_t nameproc(char *name);

/* arity.c */
int arity(Node *cur);
