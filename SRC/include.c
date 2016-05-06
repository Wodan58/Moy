/*
    module  : include.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
include  :  "filnam.ext"  ->
Transfers input to file whose name is "filnam.ext".
On end-of-file returns to previous input file.
*/
/* include.c */
USETOP(include_, "include", STRING, include(stk->u.str))
