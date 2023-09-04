/*
    module  : id.c
    version : 1.2
    date    : 09/04/23
*/
#ifndef ID_C
#define ID_C

/**
OK 1200  id  :  N	->
Identity function, does nothing.
Any program of the form  P id Q  is equivalent to just  P Q.
*/
void id_(pEnv env)
{
    env->nothing++;
/* do nothing */
}
#endif
