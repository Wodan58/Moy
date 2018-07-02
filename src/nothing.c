/*
    module  : nothing.c
    version : 1.5
    date    : 07/02/18
*/

/**
nothing  :  ->  nothing
Pushes the value nothing.
*/
PRIVATE void do_nothing(void)
{
    Node temp;

    temp.u.num = temp.op = NOTHING_;
    DUPLICATE(&temp);
}
