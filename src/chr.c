/*
    module  : chr.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef CHR_C
#define CHR_C

/**
OK 1470  chr  :  DA	I  ->  C
C is the character whose Ascii value is integer I (or logical or character).
*/
void chr_(pEnv env)
{
    Node node;

    PARM(1, PREDSUCC);
    node = lst_pop(env->stck);
    node.op = CHAR_;
    lst_push(env->stck, node);
}
#endif
