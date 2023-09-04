/*
    module  : getch.c
    version : 1.3
    date    : 09/04/23
*/
#ifndef GETCH_C
#define GETCH_C

/**
OK 3200  getch  :  A	->  N
[EXT] Reads a character from input and puts it onto stack.
*/
void getch_(pEnv env)
{
    Node node;

    node.u.num = get_char();
    node.op = CHAR_;
    lst_push(env->stck, node);
}
#endif
