/*
    module  : ylex.c
    version : 1.2
    date    : 08/23/23
*/
#include "globals.h"

#ifdef DUMP_TOKENS
static void dumptok(Token tok, int num)
{
    printf("(%d) ", num);
    switch (tok.symb) {
    case CHAR_	  : printf("'%d", (int)tok.yylval.num);
		    break;
    case STRING_  : printf("\"%s\"", tok.yylval.str);
		    break;
    case FLOAT_	  : printf("%g", tok.yylval.dbl);
		    break;
    case INTEGER_ : printf("%" PRId64, tok.yylval.num);
		    break;
    case USR_	  : printf("%s", tok.yylval.str);
		    break;
    case '['	  : printf("LBRACK");
		    break;
    case '{'	  : printf("LBRACE");
		    break;
    case '('	  : printf("LPAREN");
		    break;
    case ']'	  : printf("RBRACK");
		    break;
    case ')'	  : printf("RPAREN");
		    break;
    case '}'	  : printf("RBRACE");
		    break;
    case ';'	  : printf("SEMICOL");
		    break;
    case JEQUAL	  : printf("EQUAL");
		    break;
    case END	  : printf("END");
		    break;
    case MODULE	  : printf("MODULE");
		    break;
    case JPRIVATE : printf("PRIVATE");
		    break;
    case JPUBLIC  : printf("PUBLIC");
		    break;
    }
    printf("\n");
    fflush(stdout);
}
#endif

/*
    Push a symbol into the tokenlist.
*/
static void push_symb(pEnv env, Symbol symb)
{
    Token tok;

    tok.symb = symb;
    tok.yylval = yylval;
    vec_push(env->tokens, tok);
}

/*
    yylex - wrapper around my_yylex, storing tokens read, reading from the
	    store or just calling my_yylex itself. This allows tokens to be
	    read twice.

    After reading MODULE or JPRIVATE, read all tokens upto END, and include
    them in the tokenlist. All symbols preceding "==" are declared.
*/
int yylex(pEnv env)
{
    Token tok;
    Symbol symb;
    int module = 0, private = 0, hide = 0, modl = 0, hcnt = 0;

/*
    If there is a tokenlist, extract tokens from there.
*/
    if (vec_size(env->tokens)) {
	tok = vec_pop(env->tokens);
#ifdef DUMP_TOKENS
	dumptok(tok, 1); /* tokens from the first pop */
#endif
	symb = tok.symb;
	yylval = tok.yylval;
	return symb;
    }
/*
    There is no tokenlist, use the normal procedure to get one.
*/
    symb = my_yylex(env);
/*
    There is a token available, do some extra processing, in case the token is
    MODULE or JPRIVATE: MODULE .. END or HIDE .. END.
*/
    if (symb == MODULE || symb == JPRIVATE) {
/*
    Copy the global variables of modl.c into local variables.
*/
	savemod(&hide, &modl, &hcnt);
	do {
	    switch (symb) {
	    case MODULE	  : push_symb(env, symb);
			    symb = my_yylex(env);
			    if (symb == USR_) {
				initmod(env, yylval.str);
				module++;
			    } else
				yyerror(env, "atom expected as name of module");
			    break;
	    case JPRIVATE : initpriv(env);
			    if (!module)
				private++;
			    break;
	    case JPUBLIC  : stoppriv();
			    break;
	    case EQDEF	  : if (strchr(yylval.str, '.') == 0)
				yylval.str = classify(env, yylval.str);
			    enteratom(env, yylval.str, 0);
			    break;
	    case END	  : if (module) {
				exitmod();
				module--;
			    } else if (private) {
				exitpriv();
				private--;
			    }
			    if (!module && !private)
				goto done;
			    break;
	    }
	    push_symb(env, symb);
	    symb = my_yylex(env);
	} while (1);
/*
    Restore the global variables in modl.c from the local copies.
*/
done:	undomod(hide, modl, hcnt);
	push_symb(env, symb); /* store the last symbol that was read */
	push_symb(env, symb); /* extra sym for the benefit of reverse */
	vec_reverse(env->tokens);
    }
/*
    If there is a tokenlist, extract tokens from there.
*/
    if (vec_size(env->tokens)) {
	tok = vec_pop(env->tokens);
#ifdef DUMP_TOKENS
	dumptok(tok, 2); /* tokens from the second pop */
#endif
	symb = tok.symb;
	yylval = tok.yylval;
    } else {
#ifdef DUMP_TOKENS
	tok.symb = symb;
	tok.yylval = yylval;
	dumptok(tok, 3); /* there was no value popped */
#endif
    }
    return symb;
}
