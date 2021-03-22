/*
    module  : symbol.h
    version : 1.14
    date    : 03/15/21
*/
#ifndef SYMBOL_H
#define SYMBOL_H

#define IS_UNDEFINED	0
#define IS_ORIGINAL	1
#define IS_BUILTIN	2
#define IS_DEFINED	4
#define IS_USED		8
#define IS_ACTIVE	16
#define IS_DECLARED	32
#define IS_PRINTED	64

typedef unsigned short Operator;

typedef struct Node {
    YYSTYPE u;
    Operator op;
    struct Node *next;
} Node;

#include "node.h"
#include "environ.h"

/* interp.c */
void interprete(pEnv env, Node *code);
void execute(pEnv env, Node *code);

/* compile.c */
void printnode(pEnv env, Node *node, FILE *fp);
void printstack(pEnv env, FILE *fp);
void compile(pEnv env, Node *node);

/* initsym.c */
void initsym(pEnv env, int argc, char **argv);

/* print.c */
void writefactor(pEnv env, Node *node, FILE *stm);
void writeterm(pEnv env, Node *code, FILE *stm);
void writestack(pEnv env, Node *code, FILE *stm);

/* utils.c */
void readfactor(pEnv env, int sym);
void readterm(pEnv env, int sym);

/* symbol.c */
void initmod(char *str);
void exitmod(void);
void initpriv(void);
void stoppriv(void);
void exitpriv(void);
void initpub(void);
void exitpub(void);
char *prefix(int *hide, int *local);
char *iterate(char *name);

/* dict.c */
int symtabmax(pEnv env);
int symtabindex(pEnv env);

void init_dict(pEnv env);
int lookup(pEnv env, char *name);
void enteratom(pEnv env, char *name, Node *cur);
void dump(pEnv env);

unsigned dict_flags(pEnv env, int index);
void dict_setflags(pEnv env, int index, unsigned flags);
char *dict_descr(pEnv env, int index);
char *dict_name(pEnv env, int index);
char *dict_nickname(pEnv env, int index);
Node *dict_body(pEnv env, int index);
int dict_size(pEnv env);

int check_anything_was_printed(pEnv env);
void iterate_dict_and_write_struct(pEnv env, FILE *fp);

char *procname(proc_t proc);
proc_t nameproc(char *name);
#endif
