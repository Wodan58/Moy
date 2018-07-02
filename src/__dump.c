/*
    module  : __dump.c
    version : 1.6
    date    : 07/02/18
*/

/**
__dump  :  ->  [..]
debugging only: pushes the dump as a list.
*/
PRIVATE void do___dump(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(LIST_, 0);
}
