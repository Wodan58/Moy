/*
    module  : nothing.c
    version : 1.6
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_nothing(void)
{
    TRACE;
    do_push(start_of_text);
}
#else
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
#endif
