/*
    module  : case.c
    version : 1.17
    date    : 06/20/22
*/
#ifndef CASE_C
#define CASE_C

#include "compare.h"

/**
case  :  X [..[X Y]..]  ->  [Y] i
Indexing on the value of X, execute the matching Y.
*/
#ifdef COMPILING
void put_case(pEnv env, Node *prog)
{
    fprintf(outfp, "{ /* CASE */");
    fprintf(outfp, "int num = 0; for (;;) {");
    for (; prog->next; prog = prog->next) {
	printnode(env, prog);
	fprintf(outfp, "if (!Compare(env, env->stk->u.lis, env->stk->next)) {");
	fprintf(outfp, "POP(env->stk); POP(env->stk);");
	compile(env, prog->u.lis->next);
	fprintf(outfp, "num = 1; break; }");
    }
    fprintf(outfp, "break; } if (!num) {");
    fprintf(outfp, "POP(env->stk);");
    compile(env, prog->u.lis);
    fprintf(outfp, "} }");
}
#endif

PRIVATE void do_case(pEnv env)
{
    Node *prog;

    ONEPARAM("case");
    LIST("case");
    prog = env->stk->u.lis;
    CHECKEMPTYLIST(prog, "case");
    POP(env->stk);
    INSTANT(put_case);
    ONEPARAM("case");
    for (; prog->next; prog = prog->next)
	if (!Compare(env, prog->u.lis, env->stk))
	    break;
    if (prog->next) {
	POP(env->stk);
	exeterm(env, prog->u.lis->next);
    } else
	exeterm(env, prog->u.lis);
}
#endif
