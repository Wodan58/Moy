/*
    module  : fopen.c
    version : 1.8
    date    : 03/05/24
*/
#ifndef FOPEN_C
#define FOPEN_C

/**
Q0  OK  1890  fopen  :  DDA  P M  ->  S
[FOREIGN] The file system object with pathname P is opened with mode M
(r, w, a, etc.) and stream object S is pushed; if the open fails, file:NULL
is pushed.
*/
void fopen_(pEnv env)
{
    Node path, mode;

    PARM(2, FOPEN);
    env->stck = pvec_pop(env->stck, &mode);
    env->stck = pvec_pop(env->stck, &path);
    path.u.fil = fopen(path.u.str, mode.u.str);
    path.op = FILE_;
    env->stck = pvec_add(env->stck, path);
}
#endif
