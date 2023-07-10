/*
 *  module  : read.c
 *  version : 1.1
 *  date    : 07/10/23
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
    long set = 0;

    switch (env->token) {
    case USR_:
        lookup(env, yylval.str);
        if (!env->location && strchr(yylval.str, '.')) {
            yyerror(env, "no such field in module");
            return;
        }
        ent = sym_at(env->symtab, env->location);
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
            vec_push(env->stck, node);
        }
        break;
    case CHAR_:
    case INTEGER_:
    case STRING_:
    case FLOAT_:
        node.u = yylval;
        node.op = env->token;
        vec_push(env->stck, node);
        break;
    case '{':
        do {
            env->token = yylex(env);
            if ((env->token != CHAR_ && env->token != INTEGER_)
                || yylval.num < 0 || yylval.num >= SETSIZE)
                yyerror(env, "small numeric expected in set");
            else
                set |= ((long)1 << yylval.num);
        } while (env->token != '}');
        node.u.set = set;
        node.op = SET_;
        vec_push(env->stck, node);
        break;
    case '[':
        env->token = yylex(env);
        readterm(env);
        break;
    case '(':
        yyerror(env, "'(' not implemented");
        env->token = yylex(env);
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
            if (vec_size(env->stck)) {
                if (!node.u.lis)
                    vec_init(node.u.lis);
                vec_push(node.u.lis, vec_pop(env->stck));
            }
            env->token = yylex(env);
        } while (env->token != ']');
        if (!node.u.lis)
            vec_init(node.u.lis);
        vec_push(node.u.lis, node); /* scratch value */
        vec_reverse(node.u.lis); /* excludes scratch */
    }
    vec_push(env->stck, node);
}
