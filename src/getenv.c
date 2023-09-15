/*
    module  : getenv.c
    version : 1.5
    date    : 09/15/23
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
    node = lst_pop(env->stck);
    if ((node.u.str = getenv(node.u.str)) == 0)
	node.u.str = "";
    lst_push(env->stck, node);
}
#endif
