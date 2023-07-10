/*
    module  : genrec.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef GENREC_C
#define GENREC_C

/**
OK 2760  genrec  :  DDDDU	[B] [T] [R1] [R2]  ->  ...
Executes B, if that yields true, executes T.
Else executes R1 and then [[[B] [T] [R1] R2] genrec] R2.
*/
void genrec_(pEnv env)
{
    PARM(4, LINREC);
    cons_(env);
    cons_(env);
    cons_(env);
    _genrec_(env);
}
#endif
