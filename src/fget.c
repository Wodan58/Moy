/*
    module  : fget.c
    version : 1.6
    date    : 09/15/23
*/
#ifndef FGET_C
#define FGET_C

/**
OK 3180  fget  :  A	S  ->  S F
[EXT] Reads a factor from stream S and pushes it onto stack.
*/
void fget_(pEnv env)
{
    Node node;

    PARM(1, FGET);
    node = lst_back(env->stck);
    if (!redirect(env->filename, "fget", node.u.fil))	/* switch file */
	return;
    env->token = yylex(env);
    switch (env->token) {
    case USR_:
    case CHAR_:
    case INTEGER_:
    case STRING_:
    case FLOAT_:
    case BIGNUM_:
    case '{':
    case '[':
	readfactor(env);
	break;
    case '(':
    default:
	node.u.num = env->token;
	node.op = UNKNOWN_;
	lst_push(env->stck, node);
	break;
    }
}
#endif
