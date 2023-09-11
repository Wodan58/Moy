/*
    module  : getch.c
    version : 1.5
    date    : 09/11/23
*/
#ifndef GETCH_C
#define GETCH_C

/**
OK 3200  getch  :  A	->  N
[EXT] Reads a character from input and puts it onto stack.
*/
void getch_(pEnv env)
{
#ifndef COMPILER
    Node node;
#ifdef RUNTIME
    int ch;

    do
	ch = getchar();
    while (isspace(ch));
    node.u.num = ch;
#else
    node.u.num = get_char();
#endif
    node.op = CHAR_;
    lst_push(env->stck, node);
#endif
}
#endif
