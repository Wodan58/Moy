/*
    module  : getch.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef GETCH_C
#define GETCH_C

/**
OK 3100  getch  :  A	->  N
Reads a character from input and puts it onto stack.
*/
void getch_(pEnv env)
{
    Node node;

    node.u.num = getnextchar();
    node.op = CHAR_;
    vec_push(env->stck, node);
}
#endif
