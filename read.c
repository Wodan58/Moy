/*
 *  module  : read.c
 *  version : 1.7
 *  date    : 09/07/23
 */
#include "globals.h"

/*
    readfactor - read a factor from srcfile and push it on the stack.
                 In case of LPAREN nothing gets pushed.
*/
PUBLIC void readfactor(pEnv env) /* read a JOY factor */
{
    Node node;
    Entry ent;
    uint64_t set = 0;

    switch (env->token) {
    case USR_:
        lookup(env, yylval.str);
        if (!env->location && strchr(yylval.str, '.'))
            yyerror(env, "no such field in module");
        ent = vec_at(env->symtab, env->location);
        /* execute immediate functions at compile time */
        if (ent.flags == IMMEDIATE)
            (*ent.u.proc)(env);
        else {
            if (ent.is_user) {
                node.u.ent = env->location;
                node.op = USR_;
            } else {
                node.u.proc = ent.u.proc;
                node.op = ANON_FUNCT_;
            }
            lst_push(env->stck, node);
        }
        break;
    case CHAR_:
    case INTEGER_:
    case STRING_:
    case FLOAT_:
    case BIGNUM_:
        node.u = yylval;
        node.op = env->token;
        lst_push(env->stck, node);
        break;
    case '{':
        while ((env->token = yylex(env)) != '}')
            if ((env->token != CHAR_ && env->token != INTEGER_)
                || yylval.num < 0 || yylval.num >= SETSIZE)
                yyerror(env, "small numeric expected in set");
            else
                set |= ((int64_t)1 << yylval.num);
        node.u.set = set;
        node.op = SET_;
        lst_push(env->stck, node);
        break;
    case '[':
        env->token = yylex(env); /* read past [ */
        readterm(env);
        break;
    case '(':
        yyerror(env, "'(' not implemented");
        break;
    default:
        yyerror(env, "a factor cannot begin with this symbol");
    }
}

/*
    readterm - read a term from srcfile and push this on the stack as a list.
*/
PUBLIC void readterm(pEnv env)
{
    Node node;

    node.u.lis = 0;
    node.op = LIST_;
    if (env->token != ']') {
        do {
            readfactor(env);
            if (lst_size(env->stck)) {
                if (!node.u.lis)
                    lst_init(node.u.lis); /* initialize the list */
                lst_push(node.u.lis, lst_pop(env->stck));
            }
        } while ((env->token = yylex(env)) != ']'); /* read past factor */
        if (node.u.lis)
            reverse(node.u.lis); /* reverse the list */
    }
    lst_push(env->stck, node);
}
