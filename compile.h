/*
 *  module  : %M%
 *  version : %I%
 *  date    : %G%
 */
/* compile.h */

extern int compiling;

void initcompile(void);
void compile(Node *node);
void exitcompile(void);
