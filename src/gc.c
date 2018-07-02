/*
    module  : gc.c
    version : 1.3
    date    : 07/02/18
*/

/**
gc  :  ->
Initiates garbage collection.
*/
PRIVATE void do_gc(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    ck_collect();
}
