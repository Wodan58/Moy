/*
    module  : __html_manual.c
    version : 1.2
    date    : 07/02/18
*/

PRIVATE void make_manual(int style /* 0=plain, 1=HTML, 2=Latex */);

/**
__html_manual  :  ->
Writes this manual of all Joy primitives to output file in HTML style.
*/
PRIVATE void do___html_manual(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    make_manual(1);
}
