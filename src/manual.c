/*
    module  : manual.c
    version : 1.4
    date    : 03/12/17
*/
#include "runtime.h"

PRIVATE void make_manual(int style /* 0=plain, 1=HTML, 2=Latex */);

/*
manual  :  ->
Writes this manual of all Joy primitives to output file.
*/
PRIVATE void do_manual(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    make_manual(0);
}

/*
__html_manual  :  ->
Writes this manual of all Joy primitives to output file in HTML style.
*/
PRIVATE void do_html_manual(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    make_manual(1);
}

/*
__latex_manual  :  ->
Writes this manual of all Joy primitives to output file in Latex style
but without the head and tail.
*/
PRIVATE void do_latex_manual(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    make_manual(2);
}
