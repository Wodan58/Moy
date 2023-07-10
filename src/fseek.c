/*
    module  : fseek.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef FSEEK_C
#define FSEEK_C

/**
OK 1990  fseek  :  DDDAA	S P W  ->  S B
Stream S is repositioned to position P relative to whence-point W,
where W = 0, 1, 2 for beginning, current position, end respectively.
*/
void fseek_(pEnv env)
{
    Node node, locat, orien;

    PARM(3, FSEEK);
    orien = vec_pop(env->stck);
    locat = vec_pop(env->stck);
    node = vec_back(env->stck);
    node.u.num = fseek(node.u.fil, locat.u.num, orien.u.num) != 0;
    node.op = BOOLEAN_;
    vec_push(env->stck, node);
}
#endif
