/*
    module  : treegenrec.c
    version : 1.3
    date    : 09/11/23
*/
#ifndef TREEGENREC_C
#define TREEGENREC_C

/**
OK 2890  treegenrec  :  DDDDU	T [O1] [O2] [C]  ->  ...
T is a tree. If T is a leaf, executes O1.
Else executes O2 and then [[[O1] [O2] C] treegenrec] C.
*/
void treegenrec_(pEnv env)
{
#ifndef COMPILER /* T [O1] [O2] [C]	*/
    PARM(4, IFTE);
    cons_(env);
    cons_(env);
    ztreegenrec_(env);
#endif
}
#endif
