/*
    module  : getenv.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef GETENV_C
#define GETENV_C

/**
OK 3030  getenv  :  DA	"variable"  ->  "value"
Retrieves the value of the environment variable "variable".
*/
void getenv_(pEnv env)
{
    Node node;

    PARM(1, STRTOD);
    env->stck = pvec_pop(env->stck, &node);
    if ((node.u.str = getenv(node.u.str)) == 0)
	node.u.str = "";
    env->stck = pvec_add(env->stck, node);
}
#endif
