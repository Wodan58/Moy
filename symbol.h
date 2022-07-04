/*
    module  : symbol.h
    version : 1.16
    date    : 06/17/22
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

/* interp.c */
void exeterm(pEnv env, Node *code);
void execute(pEnv env, Node *code);
void execerror(pEnv env, char *message, const char *op);

/* compile.c */
void printnode(pEnv env, Node *node);
void printstack(pEnv env);
void compile(pEnv env, Node *node);
void initialise(pEnv env);

/* initsym.c */
void initsym(pEnv env, int argc, char **argv);

/* print.c */
void writefactor(pEnv env, Node *node);
void writeterm(pEnv env, Node *code);
void writestack(pEnv env, Node *code);

/* utils.c */
void readfactor(pEnv env, int sym);
void readterm(pEnv env, int sym);

/* module.c */
void initmod(pEnv env, char *name);
void initpriv(pEnv env, int priv);
void stoppriv(void);
void exitpriv(void);
void exitmod(void);
char *classify(pEnv env, char *name);
pEntry qualify(pEnv env, char *name);

/* dict.c */
int symtabmax(pEnv env);
int symtabindex(pEnv env);
unsigned dict_flags(pEnv env, int index);
void dict_setflags(pEnv env, int index, unsigned flags);
char *dict_descr(pEnv env, Node *node);
char *dict_name(pEnv env, int index);
char *dict_nickname(pEnv env, int index);
char *dict_translate(pEnv env, const char *name);
Node *dict_body(pEnv env, int index);
int dict_size(pEnv env);
char *procname(proc_t proc);
char *nickname(proc_t proc);
void init_dict(pEnv env);
int lookup(pEnv env, char *name);
void enteratom(pEnv env, char *name, Node *cur);
void dump_table(pEnv env);
void iterate_dict_and_write_struct(pEnv env, FILE *fp);

/* runtime.c */
proc_t nameproc(char *name);
#endif
