/*
    module  : joy.h
    version : 1.1
    date    : 10/18/15
*/
#ifndef PARSER
#include "parse.h"
#endif

typedef short Operator;
typedef YYSTYPE Types;

int yyparse();
struct Entry *initpriv(void);
void stoppriv(void);
void exitpriv(struct Entry * prev);
struct Entry *enteratom(char *name, struct Node * body);
struct Node *newnode(Operator op, YYSTYPE u, struct Node * next);
struct Node *reverse(struct Node * list);
int Keyword(char *str);
int ChrVal(char *str);
char *StrVal(char *str);
struct Entry *initmod(char *name);
void exitmod(struct Entry * sym);
void inisymboltable(void);
void PrintSymbolTable(void);
void exeterm(struct Node * n);
void HashValue(char *name);
void writestack(void);
void writeln(void);
