/*
    module  : getenv.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef GETENV_C
#define GETENV_C

/**
OK 3050  getenv  :  DA	"variable"  ->  "value"
Retrieves the value of the environment variable "variable".
*/
void getenv_(pEnv env)
{
    Node node;

    PARM(1, STRTOD);
    node = vec_pop(env->stck);
    if ((node.u.str = getenv(node.u.str)) == 0)
        node.u.str = "";
    vec_push(env->stck, node);
}
#endif
