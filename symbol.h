/*
    module  : symbol.h
    version : 1.7
    date    : 07/02/18
*/
#define IS_UNDEFINED	0
#define IS_BUILTIN	1
#define IS_DEFINED	2
#define IS_USED		4
#define IS_ACTIVE	8
#define IS_DECLARED	16
#define IS_PRINTED	32

typedef unsigned short Operator;

typedef struct Node {
    YYSTYPE u;
    Operator op;
    struct Node *next;
} Node;

typedef void (*proc_t)(void);

#include "node.h"

/* memory.c */
Node *getnode(void);
void freemem(void);

/* interp.c */
void interprete(Node *code);
void execute(Node *code);

/* compile.c */
void PrintHead(Node *node, FILE *fp);
void compile(Node *node);

/* print.c */
void writefactor(Node *node, FILE *stm);
void writeterm(Node *code, FILE *stm);
void writestack(Node *code, FILE *stm);

/* symbol.c */
void initmod(char *str);
void exitmod(void);
void initpriv(void);
void stoppriv(void);
void exitpriv(void);
void initpub(void);
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
