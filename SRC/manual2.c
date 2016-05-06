/*
    module  : manual2.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/* manual2.c */
/*
manual  :  ->
Writes this manual of all Joy primitives to output file.
*/
PRIVATE void manual_(void)
{
    make_manual(0);
}

/*
__html_manual  :  ->
Writes this manual of all Joy primitives to output file in HTML style.
*/
PRIVATE void __html_manual_(void)
{
    make_manual(1);
}

/*
__latex_manual  :  ->
Writes this manual of all Joy primitives to output file in Latex style
but without the head and tail.
*/
PRIVATE void __latex_manual_(void)
{
    make_manual(2);
}

/*
__manual_list  :  ->  L
Pushes a list L of lists (one per operator) of three documentation strings.
*/
PRIVATE void __manual_list_(void)
{
    manual_list_();
}
