/*
    module  : chr.c
    version : 1.6
    date    : 10/02/23
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
    env->stck = pvec_pop(env->stck, &node);
    node.op = CHAR_;
    env->stck = pvec_add(env->stck, node);
}
#endif
