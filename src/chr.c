/*
    module  : chr.c
    version : 1.1
    date    : 07/10/23
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
    node = vec_pop(env->stck);
    node.op = CHAR_;
    vec_push(env->stck, node);
}
#endif
