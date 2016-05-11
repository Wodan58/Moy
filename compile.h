/*
    module  : compile.h
    version : 1.1
    date    : 05/11/16
*/
/* compile.h */

extern int compiling;

void initcompile(void);
void compile(Node *node);
void exitcompile(void);
