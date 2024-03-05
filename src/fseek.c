/*
    module  : fseek.c
    version : 1.9
    date    : 03/05/24
*/
#ifndef FSEEK_C
#define FSEEK_C

/**
Q0  OK  1980  fseek  :  DDA  S P W  ->  S B
[FOREIGN] Stream S is repositioned to position P relative to whence-point W,
where W = 0, 1, 2 for beginning, current position, end respectively.
*/
void fseek_(pEnv env)
{
    Node node, locat, orien;

    PARM(3, FSEEK);
    env->stck = pvec_pop(env->stck, &orien);
    env->stck = pvec_pop(env->stck, &locat);
    node = pvec_lst(env->stck);
    node.u.num = fseek(node.u.fil, locat.u.num, orien.u.num) != 0;
    node.op = BOOLEAN_;
    env->stck = pvec_add(env->stck, node);
}
#endif
